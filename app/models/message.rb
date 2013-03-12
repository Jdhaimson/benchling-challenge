# == Schema Information
#
# Table name: messages
#
#  id         :integer          not null, primary key
#  device_id  :integer
#  created_at :datetime         not null
#  updated_at :datetime         not null
#  data       :binary
#

class Message < ActiveRecord::Base
  attr_accessible :device_id, :data
#  has_attached_file :data, :storage => :s3, :s3_credentials => "#{Rails.root}/config/s3.yml", :path => "/:id/:filename"
  belongs_to :device
end
