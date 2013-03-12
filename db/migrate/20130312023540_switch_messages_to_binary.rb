class SwitchMessagesToBinary < ActiveRecord::Migration
  def up
    change_table :messages do |t|
      t.remove :filepath
      t.remove :data_file_name
      t.remove :data_content_type
      t.remove :data_file_size
      t.remove :data_updated_at
    end
    add_column :messages, :data, :binary
  end

  def down
    remove_column :messages, :data
    add_column :messages, :filepath, :string
    add_column :messages, :data_file_name, :string
    add_column :messages, :data_content_type, :string
    add_column :messages, :data_file_size, :integer
    add_column :messages, :data_updated_at, :datetime
  end
end

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

