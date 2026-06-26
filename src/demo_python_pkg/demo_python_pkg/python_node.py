import rclpy
from rclpy.node import Node

def main():
    rclpy.init()
    node = Node('python_node')
    node.get_logger().info('haha py spot!')
    node.get_logger().warn('warn py spot!')
    rclpy.spin(node)
    rclpy.shutdown()