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
#### 2. Tình huống chỉ muốn merge 1 hoặc 1 vài commit nhất định vào 1 nhánh khác:

> Updating...
