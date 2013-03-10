class AddDataFileToMessages < ActiveRecord::Migration
  def up
    add_attachment :messages, :data
  end

  def down
    remove_attachment :messages, :data
  end
end
