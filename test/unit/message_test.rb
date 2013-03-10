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

require 'test_helper'

class MessageTest < ActiveSupport::TestCase
  # test "the truth" do
  #   assert true
  # end
end
