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
- sort
- ZADD
- ZCARD
- ZRANK
- ZCOUNT
- ZRANGE
- ZREMRANGEBYSCORE
- ZREM
- ZRANGEBYSCORE
- ZINTERSTORE
- ZUNIONSTORE

