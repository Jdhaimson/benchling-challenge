class CreateDevices < ActiveRecord::Migration
  def change
    create_table :devices do |t|
      t.integer :registration_key

      t.timestamps
    end
  end
end
