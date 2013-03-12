# == Schema Information
#
# Table name: devices
#
#  id               :integer          not null, primary key
#  registration_key :string(255)
#  created_at       :datetime         not null
#  updated_at       :datetime         not null
#

class Device < ActiveRecord::Base
  attr_accessible :registration_key
  before_create { |device| device.registration_key = SecureRandom.hex(10) }
  has_many :messages
end
