# Load the rails application
require File.expand_path('../application', __FILE__)

# Initialize the rails application
BenchlingChallenge::Application.initialize!

BenchlingChallenge::Application.configure do
  # Code for implementing fibers 
  config.middleware.insert_before ActionDispatch::ShowExceptions, Rack::FiberPool 
  config.threadsafe! 
=begin
  config.paperclip_defaults = {
    :storage => :s3,
    :s3_credentials => {
      :bucket => ENV['benchling-challenge'],
      :access_key_id => ENV['AKIAJCIEMBFMUHAJCTIQ'],
      :secret_access_key => ENV['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']
    }
  }
  require 'aws-sdk'
  require 'aws/core/http/em_http_handler'
  AWS.eager_autoload! # AWS lazyloading is not threadsafe
  AWS.config(
    :http_handler => AWS::Http::EMHttpHandler.new(
      :pool_size => 20, # by default connection pooling is off
      :async => false # if set to true all requests for this client will be asynchronous
    )
  )
=end
end
