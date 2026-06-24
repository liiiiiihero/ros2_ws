import threading
import requests

class Download:
    def download(self,url,callback_world_count):
        print(f'线程：{threading.get_ident()}开始下载：{url}')
        response =  requests.get(url)
        response.encoding = 'utf-8'
        callback_world_count(url,response.text)#调用回调

    def start_download(self,url,callback_world_count):
        #self.download(url,callback_world_count)
        #创建线程
        thread = threading.Thread(target=self.download,args=(url,callback_world_count))
        thread.start()

        #pass


def world_count(url,result):
    """
    普通函数，用于回调
    """
    print(f"{url}:{len(result)}->{result[:5]}")



def main():
    dowmload = Download
    #填入网址
    dowmload.start_download('',world_count)
    dowmload.start_download('',world_count)
    dowmload.start_download('',world_count)

