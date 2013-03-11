source 'https://rubygems.org'

gem 'rails', '3.2.11'

# Gems for async programming with pg and amazon s3
# For more info, see: https://github.com/leftbee/em-postgresql-adapter
gem 'pg'
gem 'thin'
gem 'em-postgresql-adapter', :git => 'git://github.com/leftbee/em-postgresql-adapter.git'
gem 'rack-fiber_pool',  :require => 'rack/fiber_pool'
gem 'em-synchrony', :git     => 'git://github.com/igrigorik/em-synchrony.git',
                    :require => ['em-synchrony',
                                 'em-synchrony/activerecord']

gem 'paperclip'
gem 'aws-sdk'
gem 'em_aws'

gem 'ruby-protocol-buffers'
gem 'ruby_protobuf'
gem 'varint'

# Gems used only for assets and not required
# in production environments by default.
group :assets do
  gem 'sass-rails',   '~> 3.2.3'
  gem 'coffee-rails', '~> 3.2.1'
  gem 'uglifier', '>= 1.0.3'
end

group :development do
  gem 'annotate'
  gem 'better_errors'
  gem 'binding_of_caller'
  gem 'meta_request'
end

gem 'jquery-rails'
