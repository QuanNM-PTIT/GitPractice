
# Git cơ bản
### A. Các lệnh git cơ bản:
 - Khởi tạo 1 repo mới tại thư mục hiện tại:
```
git init
```
 - Thêm 1 remote đến kho lưu trữ git trên internet:
```
git remote add <Tên remote (Nên đặt là origin)>
```
 - Xóa 1 remote trong repo hiện tại:
```
git remote rm <Tên remote>
```
 - Thêm tất cả những thay đổi trong 1 file cụ thể vào staging area:
```
git add <Tên file>
```
 - Thêm tất cả những thay đổi trong repo vào staging area:
```
git add .
```
 - Loại bỏ những thay đổi trong 1 file đã thêm vào staging area:
```
git restore --staged <Tên file>
```
 - Lưu lại những thay đổi trong staging area vào git repo:
```
git commit -m "<message>"
```
 - Đưa những thay đổi trong repo lên kho lưu trữ git:
```
git push <Tên remote> <Tên nhánh>
```
 - Tạo 1 nhánh mới từ nhánh hiện tại:
```
git branch <Tên nhánh>
```
 - Xem tất cả các nhánh hiện có:
```
git branch
```
 - Tạo 1 nhánh mới từ nhánh hiện tại và chuyển qua nhánh đó:
```
git checkout -b <Tên nhánh>
```
hoặc
```
git switch -c <Tên nhánh>
```
 - Chuyển sang 1 nhánh hiện có:
```
git checkout <Tên nhánh>
```
hoặc
```
git switch <Tên nhánh>
```
 - Xóa 1 nhánh hiện có:
```
git branch -D <Tên nhánh>
```
 - Merge 1 nhánh vào nhánh hiện tại:
```
git merge <Tên nhánh>
```
 - Kéo những thay đổi mới nhất từ kho lưu trữ git trên internet về và merge những thay đổi đó vào nhánh hiện tại:
```
git pull <Tên remote> <Tên nhánh>
```
 - Kéo những thay đổi mới nhất từ kho lưu trữ git trên internet về và KHÔNG merge những thay đổi đó vào nhánh hiện tại:
```
git fetch <Tên remote> <Tên nhánh>
```
 - Xem trạng thái những thay đổi hiện tại trong repo:
```
git status
```
 - Xem lịch sử commit trên nhánh hiện tại:
```
git log
```
 - Xem lịch sử commit trên nhánh hiện tại trên 1 dòng:
```
git log --oneline
```
### B. Các tình huống mô phỏng thường gặp và cách xử lý:
#### 1. Tình huống conflict code: 
> **Mô tả tình huống**: Bạn A và bạn B cùng  tạo 1 nhánh mới từ nhánh dev. Bạn A chỉnh sửa file main.c sau đó push lên nhánh a-dev và tạo 1 pull/merge request vào nhánh dev sau đó tiến hành merge. Sau khi bạn A đã merge nhánh của mình vào nhánh dev, bạn B cũng chỉnh sửa file main.c và chỉnh sửa cùng 1 vị trí với bạn A, sau đó bạn B push lên nhánh b-dev và tạo pull/merge request vào nhánh dev. Khi bạn B tiến hành merge vào nhánh dev thì lúc này không thể merge được vì xảy ra conflict code với bạn A tại file main.c trong repo. Đây là tình huống giả định xảy ra với 1 file main.c, trong thực tế có thể bạn sẽ còn gặp trường hợp conflict trên nhiều file, nhưng cách xử lý thì tương tự nhau.

 - **Phương pháp xử lý**: Lúc này ta sẽ xử lý trên local (Trên máy tính, PC cá nhân). Bạn B sẽ tiến hành checkout sang nhánh dev (Nhánh sẽ được merge) và kéo những thay đổi mới nhất về bằng lệnh ```git pull <Tên remote> dev``` và sau đó checkout sang nhánh b-dev (Nhánh sẽ bị merge), ta tiến hành merge nhánh dev vào nhánh b-dev để conflict xảy ra. Khi xảy ra conflict, ta truy cập vào các file bị conflict và xử lý, chọn 1 trong 3 lựa chọn:
	 - Accept current change: Sử dụng những thay đổi của bạn B.
	 - Accept incoming change: Sử dụng những thay đổi của bạn A.
	 - Accept both changes: Sử dụng những thay đổi của cả 2 bạn.
- Sau khi resolve conflict xong, bạn B sẽ đưa các thay đổi vào staging area, commit và push lại lên nhánh b-dev. Lúc này sẽ hết conflict và có thể tiến hành merge request của bạn B.
#### 2. Tình huống chỉ muốn merge 1 hoặc 1 vài commit nhất định từ 1 nhành vào 1 nhánh khác:

> Updating...

# Bài tập:
### Đề bài: Xây dựng 1 hệ thống quản lý thư viện đơn giản bằng ngôn ngữ C++.
> Các thông tin sẽ được lưu trữ trong file .txt tương ứng (Coi mỗi file .txt là 1 database trong thực tế).
#### 1. Mô tả các thuộc tính của các class:
- Class Book:
	- id: int
	- title: string
	- author: string
	- quantity: int
- Class EBook kế thừa class Book và có thêm các thuộc tính:
	- fileFormat: string
	- fileSize: int
- Class Person:
	- id: int
	- name: string
	- email: string
	- sex: string
	- birthdate: string
	- address: string
	- phoneNumber: string
	- role: string
- Class BorrowInfo:
	- id: int
	- personId: int
	- bookId: int
	- eBookId: int
- Class User:
	- id: int
	- email: string
	- password: string
#### 2. Mô tả các methods của các class (Các tham số các bạn tự chọn):
- Class Book:
	- Book(): Hàm khởi tạo 1 cuốn sách với các thông tin tương ứng. Các thông tin cần được validate. Id sẽ tự động nhận là id bé nhất chưa xuất hiện trong file books.txt và không truyền id vào constructor.
	- addBook(): Thêm thông tin 1 cuốn sách vào file books.txt. Chỉ người
	- getBooks(): Lấy tất các các thông tin các cuốn sách có trong file books.txt và trả về 1 vector Book.
	- updateBook(): Cập nhật thông tin của 1 cuốn sách trong file books.txt theo id. Các thông tin cũng cần được validate.
	- deleteBook(): Xóa thông tin 1 cuốn sách trong file books.txt theo id. Cần được validate xem id có tồn tại không trước khi xóa.
- Class EBook có thể override lại các methods trong class Book (Nếu cần).
- Class Person:
	- Person(): Hàm khởi tạo 1 người với các thông tin tương ứng. Các thông tin cần được validate. Id sẽ tự động nhận là id bé nhất chưa xuất hiện trong file people.txt và không truyền id vào constructor.
- Class User:
	- User(): Hàm khởi tạo thông tin 1 user với các thông tin tương ứng. Các thông tin cần được validate. Id sẽ tự động nhận là id bé nhất chưa xuất hiện trong file users.txt và không truyền id vào constructor.
	- register(): Thêm thông tin đăng nhập 1 user vào file users.txt. Chú ý validate dữ liệu (email không được trùng, password cần có thêm rule gì đó các bạn tự quy định).
	- login(): Kiểm tra thông tin đăng nhập và trả về Person với email tương ứng.
	- logout(): Đăng xuất.
- Class BorrowInfo():
	- BorrowInfo(): Hàm khởi tạo 1 thông tin mượn sách mới với các thông tin tương ứng. Các thông tin cần được validate. Id sẽ tự động nhận là id bé nhất chưa xuất hiện trong file borrowInfos.txt và không truyền id vào constructor.
	- addInfo(): Thêm thông tin mượn sách vào file borrowInfos.txt, validate dữ liệu đầu vào.
	- updateInfo(): Cập nhật thông tin mượn sách vào file borrowInfos.txt, validate dữ liệu đầu vào.

> Các methods trên có thể chưa đủ, các bạn có thể thêm các methods khác nếu cần thiết.

#### 3. Kịch bản thao tác:
- Khi chạy chương trình, sẽ hiển thị ra 1 menu lựa chọn:
	- 1. Đăng nhập: Nếu người dùng chọn chức năng này sẽ cho phép nhập vào thông tin đăng nhập và xác thực thông tin, nếu đăng nhập thành công sẽ in ra dòng chữ "Welcome <tên>!". Các chức năng từ chức năng thứ 3 trở đi sẽ phải yêu cầu người dùng đăng nhập mới có thể thao tác.
	- 2. Đăng ký: Cho phép người dùng đăng ký tài khoản, role mặc định sẽ là user.

	- 3. Thêm sách: Chỉ thực hiện được nếu người dùng có role admin. Sẽ cho phép người dùng thêm thông tin 1 cuốn sách mới.
	- 4. Sửa thông tin sách: Chỉ thực hiện được nếu người dùng có role admin. Sẽ cho phép người dùng nhập vào id cuốn sách và cho phép sửa thông tin cuốn sách đó.
	- 5. Xóa sách: Chỉ thực hiện được nếu người dùng có role admin. Cho phép người dùng nhập vào id cuốn sách, và có xác nhận trước khi xóa.
	- 6. Mượn sách: Chỉ thực hiện được nếu người dùng có role user. Cho phép người dùng nhập vào id cuốn sách muốn mượn.
	- 7. Trả sách: Chỉ thực hiện được nếu người dùng có role user. Cho phép người dùng nhập vào id cuốn sách muốn trả.
	- 8. Lấy thông tin các quyển sách: Hiển thị toàn bộ danh sách các cuốn sách hiện có trong file books.txt. Các thông tin hiển thị theo thứ tự id tăng dần.
	- 9. Lấy thông tin 1 quyển sách: Cho phép người dùng nhập vào id 1 quyển sách và hiển thị thông tin quyển sách đó.
	- 10. Lấy thông tin tất cả các eBook hiện có.
	- 11. Lấy thông tin 1 eBook có id nằm trong file eBooks.txt.
	- 13. Hiển thị tất cả các quyển sách đã mượn của bản thân (Đối với role user).
	- 14. Hiển thị tất cả các quyển sách của 1 người dùng đã mượn với id người dùng: Cho phép người dùng có role admin nhập vào id của 1 người dùng và hiển thị thông tin các quyển sách mà người dùng đó đã mượn.
	- 15. Chỉnh sửa thông tin cá nhân: Cho phép người dùng chỉnh sửa thông tin cá nhân, trừ role và id.
	- 16. Chỉnh sửa thông tin cá nhân của người khác: Chỉ thực hiện được nếu người dùng có role admin. Cho phép người dùng nhập nhập vào id của 1 user và chỉnh sửa thông tin của user đó, có thể cập nhật role cho user đó lên admin, nhưng không được chỉnh sửa id.
	- 17. Đăng xuất.
	- 18. Thoát chương trình.

#### 4. Phân chia công việc:
- Công việc 1:
	- Xây dựng class Book, EBook cùng các methods bên trong nó.
	-  Làm các tính năng có số thứ tự là số lẻ.
- Công việc 2:
	- Xây dựng class Person, BorrowInfo cùng các methods bên trong nó.
	- Làm các tính năng có số thứ tự là số chẵn. 
