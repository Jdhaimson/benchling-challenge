class MessagesController < ApplicationController
  def index
    @messages = Message.where("device_id = #{params[:device_id]}")
  end

  def new
    @device_id = params[:device_id]
    @device = Device.find(@device_id)
    @message = @device.messages.build
  end

  def create
    @message = Message.create(params[:message])
    redirect_to Device.find(params[:message][:device_id])
  end

  def show
    @message = Message.find(params[:id])
  end

  def test
    require 'probuff.pb' 
    msg = ProBuff::MyMessage.new( registration_key: "123456789", device_id: 6 )
    msg.data.append("Hello World")
    @messageenc = msg.to_s
    @messagedec = msg.parse_from_string(@messageenc)
  end
end
