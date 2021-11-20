# multi-client-socket
Multi-client socket chat and read file

# Lý thuyết socket
Về cơ bản có 2 loại chính là TCP (Stream) socket và UDP (datagram) socket. Đây cũng là 2 loại socket được sử dụng nhiều nhất.
  - Stream Socket, còn gọi là TCP socket, bởi nó sử dụng giao thức TCP:
    - Yêu cầu kết nối: 2 phía bắt buộc phải được thiết lập kết nối trước khi gửi dữ liệu.
    - Đảm bảo dữ liệu: Dữ liệu được gửi sẽ đến đúng nơi, đúng thứ tự.
    - Có xác nhận: Người gửi sẽ có xác nhận trả về cho dù có gửi thành công hay không.
    - Ứng dụng: Truyền tài văn bản (chat, HTTP), truyền file (FTP), v.v
  - Datagram Socket, còn gọi là UDP socket, sử dụng giao thức UDP:
    - Không yêu cầu kết nối: 2 phía không cần thiết phải thiết lập kết nối trước khi gửi. Thông tin về người nhận có ở trong gói tin luôn.
    - Dữ liệu không đảm bảo: Thứ tự nhận được có thể khác với thứ tự gửi đi, mất gói tin.
    - Không xác nhận: người gửi không biết được tình trạng gói tin đã gửi.
    - Quá trình kết nối và gửi nhanh, đơn giản.
    - Ứng dụng: video stream, online game, v.v

Ngoài ra còn nhiều loại socket khác: 
  - Raw socket: để hỗ trợ phát triển giao thức truyền tải mới
  - Sequence Packet socket (SEQPACK): gói tin có trình tự, hướng kết nối
  - v.v

# Giới thiệu chương trình
Đây là client-server TCP socket với các chức năng:
  - Nhiều client kết nối với server
  - Các client chat với nhau
  - Các client có thể liệt kê danh sách file trên server và đọc file
  - Server sử dụng select() để xử lý nhiều client (nhiều fd) cùng lúc
  - Client sử dụng pthread để input và output cùng lúc

# Sử dụng
- Chạy server trước
- Khi chạy client cần truyền vào tham số là địa chỉ IP của server, ví dụ:
  ```./client 192.168.1.13```
- Từ client, có thể gửi tin nhắn với nội dung bất kỳ, hoặc là gõ 1 trong 3 lệnh:
  - `/listf` Để liệt kê danh sách file có trên server
  - `/readf <filename>` Để đọc file có tên là <filename> trên server
  - `/close` Để đóng kết nối
  
# Demo
  ![image](https://user-images.githubusercontent.com/29064137/142719260-7bd8271b-5551-469f-ae1a-bffac46a67e9.png)
