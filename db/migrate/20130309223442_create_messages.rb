class CreateMessages < ActiveRecord::Migration
  def change
    create_table :messages do |t|
      t.integer :device_id
      t.string :filepath

      t.timestamps
    end
  end
end
