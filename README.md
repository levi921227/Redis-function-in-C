# Redis function in C
本篇主要是想透過 C 語言來實施類似 Redis 的 NoSQL 資料庫操作，包括基本的 CRUD 及其他衍生功能，接下來會介紹個檔案中的功能與作用。
開發環境: Ubuntu 22.04

## Basic CMD
主要包含最基本的 Create, Read, Update, Delete 以及顯示所有 key-value pairs 的功能。

## List CMD
針對 List 操作的命令，包含
- LPUSH: 新增元素到 list 頭部
- LPOP: 移除 list 第一個元素
- RPUSH: 新增元素到 list 底部
- RPOP: 移除 list 最後一個元素
- LRANGE: 獲取指定範圍內的元素
- LLEN: 獲取 list的長度

## Sorted-List CMD
針對排序後的 List 操作的命令，包含
- sort: 利用 Merge sort 將序列由小到大排序
- ZADD: 對 sorted-list 添加一個元素
- ZCARD: 獲得 sorted-list 的元素個數
- ZRANK: 返回 sorted-list 指定元素的索引
- ZCOUNT: 計算指定 value 區間的元素個數
- ZRANGE: 返回指定索引區間的所有元素
- ZREMRANGEBYSCORE: 移除指定 value 間的所有元素
- ZREM: 移除 sorted-list 中的元素
- ZRANGEBYSCORE: 返回指定 value 間的所有元素
- ZINTERSTORE: 計算一個或多個 sorted-list 中的交集並存於新的 sorted-list 中
- ZUNIONSTORE: 計算一個或多個 sorted-list 的聯集並存於新的 key 中

## Performance Test
主要將 **Basic CMD** 中的功能與呼叫 Redis function 的性能做比較，比較方式為隨機產生 100000 組 key-value pairs 並分別計算 Create 和 Read 的總時間與平均時間，同時也會比較消耗的記憶體大小

