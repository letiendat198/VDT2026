# VDT2026 Mini Project: GisVDT

## TODO:
- Bắt buộc:
    - ~~Nối signal selection với insert watch polygon để insert vùng select~~
    - ~~Vẽ vùng select~~
    - ~~Highlight và hiện thông báo tàu đi vào vùng select~~
    - ~~Bỏ rectangle selection~~
    - ~~Fix mấy cái binding loop~~ 
    - ~~Tính năng delete zone~~
- Optional:
    - ~~Viết logic update vị trí tàu trên bản đồ bẳng ID để tránh nháy khi update~~ (Phải subclass lại QAbstractListModel)
    - ~~Popup hiển thị thông tin cập nhật realtime thay vì thông tin lúc bấm vào~~
    - ~~Viết QtQuickPaintedItem để vẽ Ship marker thành dạng mũi tên~~ (Dùng SVG)
    - Thêm icon cho các nút
    - ~~Overlay Hoàng Sa, Trường Sa~~
    - ~~Check lại cái đống thread~~
    - ~~Notification queue~~
    - ~~Cho phép sửa cài đặt postgres để còn package~~
    - ~~Package~~
    - ~~Fix memory leak~~ (Không có memory leak ở Ba Sing Se...) (But fr ko hiểu sao trước đó memory cứ tăng dần, giờ lại bình thường) 
    - ~~Error popup~~
    - ~~Catch socket init error~~
    - ~~Fix lỗi mỗi lần read dùng 1 thread, không dùng lại db được~~
    - Cẩn thận nếu spawn nhiều runnable, rồi giảm số lượng, sẽ có thread bị orphan dẫn đến
    db connection cũng bị orphan, làm tốn tài nguyên. Tìm cách close DB khi thread exit