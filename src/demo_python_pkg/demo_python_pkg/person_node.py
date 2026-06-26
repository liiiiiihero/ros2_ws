import rclpy
from rclpy.node import Node

class PersonNode(Node):
    def __init__(
            self,
            node_name_v:str,
            name_v:str,
            age_v:int,
            ) -> None:
        print('using for adding two factors')
        super().__init__(node_name_v)
        self.name = name_v
        self.age = age_v

    def love(self, lover_v:str) :
        """
        way : love
        
        """
        self.get_logger().info(f"{self.age}th,{self.name},love {lover_v}")


def main():
    rclpy.init()
    node = PersonNode('Li,xiaolihaha', 18)
    xiaodi = PersonNode('di,xiaodihahah', 18)
    node.love('xiaodi')
    xiaodi.love('xiaoli')
    rclpy.spin(node)
    rclpy.shutdown()
