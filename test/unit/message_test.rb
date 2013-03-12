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

require 'test_helper'

class MessageTest < ActiveSupport::TestCase
  # test "the truth" do
  #   assert true
  # end
end
