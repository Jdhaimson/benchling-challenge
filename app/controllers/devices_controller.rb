class DevicesController < ApplicationController
  def index
    @device = Device.new
    @devices = Device.all
  end

  def create
    @device = Device.create()
    flash[:success] = "Your device key is: #{@device.registration_key} and your device id is: #{@device.id}"
    redirect_to @device
  end

  def show
    @device = Device.find(params[:id])

    #Pull last message and decode the data
    require 'probuff.pb'
    pb = ProBuff::MyMessage.new 
    @message = pb.parse_from_string(@device.messages.last.data).as_json
  end
end
