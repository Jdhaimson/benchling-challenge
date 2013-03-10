class Message < ActiveRecord::Base
  attr_accessible :device_id, :filepath
  has_attached_file :data
end
