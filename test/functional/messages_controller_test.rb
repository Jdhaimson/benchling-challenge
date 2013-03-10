require 'test_helper'

class MessagesControllerTest < ActionController::TestCase
  test "should get index" do
    get :index
    assert_response :success
  end

  test "should get receive" do
    get :receive
    assert_response :success
  end

  test "should get create" do
    get :create
    assert_response :success
  end

end
