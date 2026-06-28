import  launch
import  launch_ros

def generate_launch_description():
    """"产生launch描述"""
    action_node_patrol_client = launch_ros.actions.Node(
        package = 'demo_cpp_service',
        executable='patrol_client',
        output = 'screen'
    )
    action_node_turtle_control = launch_ros.actions.Node(
        package = 'demo_cpp_service',
        executable='turtle_control',
        output = 'log'
    )
    # action_node_turtle_cmd = launch_ros.actions.Node(
    #     package = 'demo_topic_cpp',
    #     executable='turtle_cmd',
    #     output = 'both'
    # )

    return launch.LaunchDescription([
        #actions 动作
        action_node_patrol_client,
        action_node_turtle_control,
        # action_node_turtle_cmd,

   ] )

