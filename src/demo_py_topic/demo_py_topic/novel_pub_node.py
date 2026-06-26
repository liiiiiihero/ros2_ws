import rclpy
from rclpy.node import Node
import requests
from example_interfaces.msg import String
from queue import Queue

class Novel_pub(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info(f'{node_name},启动!')
        self.novel_queue = Queue()#队列
        self.novel_publisher_ = self.create_publisher(String,'novel',10)
        self.create_timer(5,self.timer_callback)
        
    def timer_callback(self):
        line = self.novel_queue.get()
        msg =String()#组装
        msg.data = line
        self.novel_publisher_.publish(msg)

    def download(self,url,callback_world_count):
        response =  requests.get(url)
        response.encoding = 'utf-8'


def main():
    rclpy.init()
    node = Novel_pub('novel_pub')
    node.download()
    rclpy.spin(node)
    rclpy.shutdown()