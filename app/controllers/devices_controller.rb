class DevicesController < ApplicationController
  def index
    @device = Device.new
  end

  def create
    @device = Device.create()
    flash[:success] = "Your device key is: #{@device.registration_key} and your device id is: #{@device.id}"
    redirect_to @device
  end

  def show
    @device = Device.find(params[:id])
    @message = @device.messages.last
  end
end
