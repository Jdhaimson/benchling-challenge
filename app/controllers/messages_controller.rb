class MessagesController < ApplicationController
  def index
    @message = Message.last
  end

  def new
    @message = Message.new() 
  end

  def create
    @message = Message.create(params[:message])
    redirect_to @message
  end

  def show
    @message = Message.find(params[:id])
  end
end
