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
    redirect_to @message
  end

  def show
    @message = Message.find(params[:id])
  end
end
