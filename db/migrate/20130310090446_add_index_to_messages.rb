class AddIndexToMessages < ActiveRecord::Migration
  def change
    add_index :messages, :device_id
  end
end
