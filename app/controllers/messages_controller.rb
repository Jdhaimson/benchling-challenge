class MessagesController < ApplicationController
  def index
    #Find and decode all of the messages
    require 'probuff.pb'
    @messages = []
    Message.where("device_id = #{params[:device_id]}").each do |message_enc|
      msg = ProBuff::MyMessage.new 
      @messages.append(msg.parse_from_string(message_enc.data).as_json)
    end
  end

  def new
    @device_id = params[:device_id]
    @device = Device.find(@device_id)
    @message = @device.messages.build
  end

  def create 
    device_id = (params[:message][:device_id]).to_i
    device = Device.find(device_id)

    #Authenticate the device
    reg_key = params[:message][:registration_key]
    if reg_key != device.registration_key
      flash[ failure: "You have the incorrect registration key" ]
      redirect_to device 
    end

    #Encode the data with ProtoBuf
    require 'probuff.pb'
    data = params[:message][:data]
    msg = ProBuff::MyMessage.new( registration_key: reg_key, device_id: device_id )
    msg.data = [data]
    encoded_data = msg.to_s
    @message = Message.create(device_id: device_id, data: encoded_data )
    redirect_to device
  end

  def receive
    device_id = (params[:message][:device_id]).to_i
    device = Device.find(device_id)

    #Authenticate the device
    reg_key = params[:message][:registration_key]
    if reg_key != device.registration_key
      flash[ failure: "You have the incorrect registration key" ]
      redirect_to device 
    end

    Message.create( device_id: device_id, data: params[:message][:data] )
    redirect_to device
  end

  def show
    enc_message = Message.find(params[:id])

    #Decode the data
    require 'probuff.pb'
    pb = ProBuff::MyMessage.new 
    @message = pb.parse_from_string(enc_message.data).as_json
  end

end
