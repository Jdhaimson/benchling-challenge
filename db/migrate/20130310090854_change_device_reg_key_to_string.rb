class ChangeDeviceRegKeyToString < ActiveRecord::Migration
  def up
    change_column :devices, :registration_key, :string
  end

  def down
    change_column :devices, :registration_key, :integer
  end
end
