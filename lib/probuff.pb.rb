### Generated by rprotoc. DO NOT EDIT!
### <proto file: config/probuff.proto>
# package ProBuff;
# 
# message MyMessage {
#   required string registration_key = 1;
#   required int32 device_id = 2;
#   repeated string data = 3;
#   repeated bytes binary_data = 4;
# }

require 'protobuf/message/message'
require 'protobuf/message/enum'
require 'protobuf/message/service'
require 'protobuf/message/extend'

module ProBuff
  class MyMessage < ::Protobuf::Message
    defined_in __FILE__
    required :string, :registration_key, 1
    required :int32, :device_id, 2
    repeated :string, :data, 3
    repeated :bytes, :binary_data, 4
  end
end
