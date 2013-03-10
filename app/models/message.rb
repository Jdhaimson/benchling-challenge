# == Schema Information
#
# Table name: messages
#
#  id                :integer          not null, primary key
#  device_id         :integer
#  filepath          :string(255)
#  created_at        :datetime         not null
#  updated_at        :datetime         not null
#  data_file_name    :string(255)
#  data_content_type :string(255)
#  data_file_size    :integer
#  data_updated_at   :datetime
#

class Message < ActiveRecord::Base
  attr_accessible :device_id, :filepath, :data
  has_attached_file :data, :storage => :s3, :s3_credentials => "#{Rails.root}/config/s3.yml", :path => "/:id/:filename"
  belongs_to :device
end
