[README.md](https://github.com/user-attachments/files/33953217/README.md)
# Quản lý sản phẩm bằng cây nhị phân tìm kiếm (BST) - C++

## Giới thiệu

Chương trình cài đặt cây nhị phân tìm kiếm (BST) bằng C++ để quản lý danh mục sản phẩm của một cửa hàng nhỏ. Mỗi node lưu thông tin một sản phẩm và hai con trỏ tới node con trái, node con phải. Khóa so sánh là mã sản phẩm `maSP`.

- Mã nhỏ hơn mã tại node hiện tại: đi sang cây con trái.
- Mã lớn hơn mã tại node hiện tại: đi sang cây con phải.
- Mã đã tồn tại: không tạo node mới, in "Ma san pham da ton tai".

Chương trình hỗ trợ: thêm, tìm kiếm, xóa, in danh sách tăng dần (LNR), đếm node, tính chiều cao, nạp dữ liệu mẫu, vẽ hình dạng cây và tự kiểm thử.

## Cấu trúc dữ liệu

```cpp
struct Product {
    int maSP;
    char tenSP[50];   // tối đa 49 ký tự
    int soLuong;
    double donGia;
};

struct Node {
    Product data;
    Node* left;
    Node* right;
};
```

Ràng buộc dữ liệu: `maSP > 0`, `soLuong >= 0`, `donGia >= 0`, `tenSP` không rỗng.

## Cây mẫu

Chèn lần lượt 50, 30, 70, 20, 40, 60, 80 cho cây:

```text
        50
      /    \
    30      70
   /  \    /  \
  20  40  60  80
```

Duyệt LNR cho thứ tự 20, 30, 40, 50, 60, 70, 80; số node là 7, chiều cao là 3 (cây rỗng có chiều cao 0, tính theo số node trên đường dài nhất).

## Các chức năng và hàm chính

| Chức năng | Hàm | Ghi chú |
|---|---|---|
| Tạo node | `khoiTaoNode()` | `new(nothrow)`, kiểm tra `NULL` |
| Kiểm tra dữ liệu | `loiDuLieu()` | Trả về `NULL` nếu hợp lệ, ngược lại là nội dung lỗi |
| F1 Thêm | `themSanPham()` | Duyệt bằng con trỏ cấp 2, trả về OK / TRUNG / SAI / HET_BO_NHO |
| F2 Tìm | `timSanPham()` | Duyệt lặp, trả về `NULL` nếu không thấy |
| F3 Xóa | `xoaNode()` | Đủ 3 trường hợp, dùng inorder successor |
| F4 In tăng dần | `duyetLNR()` | Left - Node - Right |
| F5 Đếm | `demNut()`, `chieuCao()` | Đệ quy |
| F6 Menu | `main()` | Lặp đến khi chọn 0 |
| F7 Giải phóng | `giaiPhong()` | Hậu thứ tự: trái, phải, rồi node |
| Phụ trợ | `laBST()`, `veCay()`, `chayKiemThu()` | Kiểm tra bất biến, vẽ cây, 17 ca test |

### Xóa node (`xoaNode`)

1. **Node lá:** giải phóng node, con trỏ cha trỏ về `NULL`.
2. **Node một con:** con duy nhất (trái hoặc phải) được nối lên thay node bị xóa.
3. **Node hai con:** tìm node nhỏ nhất của cây con phải (nút kế tiếp trung thứ tự), chép toàn bộ dữ liệu sản phẩm lên node cần xóa, rồi xóa node kế tiếp đó ở vị trí cũ. Vì mọi khóa trong cây con phải đều lớn hơn khóa trái và node kế tiếp là nhỏ nhất trong số đó, bất biến BST được giữ nguyên.

Duyệt LNR luôn tăng dần vì với mỗi node, mọi khóa bên trái nhỏ hơn node và mọi khóa bên phải lớn hơn node; duyệt trái trước, node ở giữa, phải sau nên các khóa được in theo thứ tự tăng.

## Cách biên dịch và chạy

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o bst src/main.cpp
./bst            # chạy menu
./bst --test     # chạy 17 ca kiểm thử tự động
```

Menu:

```text
========== QUAN LY SAN PHAM BST ==========
1. Them san pham
2. Tim kiem san pham theo ma
3. Xoa san pham theo ma
4. In danh sach tang dan theo ma (LNR)
5. Dem so nut va chieu cao cay
6. Nap 7 san pham mau
7. Hien thi hinh dang cay
8. Chay kiem thu tu dong
0. Thoat
```

Chương trình in chữ không dấu để không bị lỗi font trên console Windows.

## Kiểm thử

Kết quả chạy `./bst --test`: **17 PASS, 0 FAIL**. Đầu ra đầy đủ nằm trong `evidence/04_ket_qua_kiem_thu_tu_dong.txt`.

| ID | Mục tiêu | Đầu vào | Kết quả kỳ vọng | Kết quả | 
|---|---|---|---|---|
| T01 | Cây rỗng | Chưa chèn gì | nút=0, cao=0, tìm 50 không thấy | Pass |
| T02 | Duyệt LNR cây mẫu | Chèn 50,30,70,20,40,60,80 | 20 30 40 50 60 70 80 | Pass |
| T03 | Đếm nút, chiều cao | Cây mẫu | nút=7, cao=3 | Pass |
| T04 | Tìm mã tồn tại | Tìm 60 | Sổ tay, 25, 25000 | Pass |
| T05 | Tìm mã không tồn tại | Tìm 99 | Không tìm thấy | Pass |
| T06 | Chèn trùng mã | Chèn lại 50 | Bị từ chối, nút vẫn là 7, tên giữ nguyên | Pass |
| T07 | Dữ liệu sai | maSP=0; maSP=-5; soLuong=-1; donGia=-1; tên rỗng | Từ chối cả 5, nút vẫn là 7 | Pass |
| T08 | Biên: tên 49 ký tự, soLuong=0, donGia=0 | Chèn mã 90 | Thêm được, nút=8, cao=4 | Pass |
| T09 | Xóa node lá | Xóa 20 | LNR: 30 40 50 60 70 80, nút=6 | Pass |
| T10 | Xóa node một con | Sau T09, xóa 30 | LNR: 40 50 60 70 80, con trái gốc là 40 | Pass |
| T11 | Xóa node hai con | Xóa 70 trên cây ban đầu | LNR: 20 30 40 50 60 80, con phải gốc là 80 | Pass |
| T12 | Xóa node gốc | Xóa 50 trên cây ban đầu | Gốc mới là 60, vẫn là BST | Pass |
| T13 | Xóa mã không tồn tại | Xóa 99 | Không xóa, nút vẫn là 7 | Pass |
| T14 | Xóa trên cây rỗng | Xóa 10 | Không xóa, cây vẫn rỗng | Pass |
| T15 | Cây suy biến và cây cân đối | Chèn 10..70 tăng dần; chèn 40,20,60,10,30,50,70 | Cao 7 và cao 3 (cùng 7 nút) | Pass |
| T16 | Nhiều phép xóa liên tiếp | Xóa 20, 30, 70, 50 | Vẫn là BST, LNR: 40 60 80 | Pass |
| T17 | Giải phóng cây | `giaiPhong()` | Gốc `NULL`, nút=0 | Pass |

Chương trình cũng được biên dịch với `-fsanitize=address,undefined` và chạy các kịch bản xóa gốc, xóa lá, thoát: không có lỗi truy cập bộ nhớ và không rò rỉ.

## Đánh giá độ phức tạp

| Thao tác | Cây cân đối | Cây suy biến |
|---|---|---|
| Tìm, chèn, xóa | O(log n) | O(n) |
| Duyệt LNR, đếm, giải phóng | O(n) | O(n) |

Hiệu năng phụ thuộc thứ tự chèn: 7 node chèn tăng dần cho chiều cao 7 (thành danh sách liên kết), còn thứ tự 40, 20, 60, 10, 30, 50, 70 cho chiều cao 3. Đây là hạn chế của BST thường; AVL hoặc Red-Black sẽ khắc phục.

## Hạn chế và hướng cải tiến

- Cây không tự cân bằng nên có thể suy biến.
- Dữ liệu chỉ lưu trong bộ nhớ, chưa ghi tệp.
- Chưa có chức năng sửa số lượng, đơn giá của sản phẩm.

## Tác giả

- Họ tên: <Họ tên>   MSSV: <MSSV>   Lớp: <Lớp>
- Môn: Cấu trúc dữ liệu và giải thuật
- Bài thực hành: Quản lý sản phẩm bằng cây nhị phân tìm kiếm (BST)
