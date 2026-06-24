import rclpy
from rclpy.node import Node
from demo_python_pkg.person_node import PersonNode

class WriterNode(PersonNode):
    def __init__(
            self,
            node_name_v:str,
            name_v:str,
            age_v:int,
            book_name_v:str,
            ) -> None:
        print('using for adding writer two factors')
        super().__init__(node_name_v, name_v, age_v)
        self.bookname = book_name_v

    def write(self, book_name_v: str) -> None:
        self.get_logger().info(f'{self.name} writes {book_name_v} ')


def main():
    rclpy.init()
    liii = WriterNode('Writer_node','xiaoli', 18, 'falling in love with')
    liii.write('falling in love with')
    rclpy.spin(liii)
    rclpy.shutdown()