class MessagesController < ApplicationController
  fpkey = "A8M9tFeDoTy2fF6x6TzSCz"

  def index
    @message = Message.last
  end

  def new
    @message = Message.new 
  end

  def create
#    posted = params[:message]
#    Dir.mkdir("#{Rails.root}/public/test")
    devid = params[:device_id]
    @message = Message.create(params[:message])
     
#    @filesuccess = File.open("#{Rails.root}/public/test/helloworld.txt", "w") { |file| file.write(params[:data]) } if !params[:data].nil?
#    @message.create( filepath: posted.filepath )
  end
end
