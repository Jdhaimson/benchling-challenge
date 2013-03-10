# Load the rails application
require File.expand_path('../application', __FILE__)

# Initialize the rails application
BenchlingChallenge::Application.initialize!

BenchlingChallenge::Application.configure do
  config.paperclip_defaults = {
    :storage => :s3,
    :s3_credentials => {
      :bucket => ENV['benchling-challenge'],
      :access_key_id => ENV['AKIAJCIEMBFMUHAJCTIQ'],
      :secret_access_key => ENV['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']
    }
  }

  # Code for implementing fibers 
  config.middleware.insert_before ActionDispatch::ShowExceptions, Rack::FiberPool 
  config.threadsafe! 

end
