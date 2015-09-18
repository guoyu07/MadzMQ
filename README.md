# MadzMQ
**MadzMQ**是基于**libzmq** + **czmq**实现的高性能，高可用的消息队列

##架构设计
```
*--------------------*
|      madclient     |
+--------------------+
|       DEALER       |
'--------------------'
          |
          |
         [1]
          |
          |
          v
.--------------------.
|       ROUTER       |
+--------------------+
| madqueue[4]        |
|--------------------|
|      madbroker     |
+-----+--------------+
| PUB | ROUTER  |    |
'-----+----+----+----+
   |       ^
   |       |
   |       |
  [2]     [3]
   |       |
   |       | 
   v       |
.-----+----+----+----.
| SUB | DEALER  |    |
+--------------------+
|      madserver     |
*--------------------*
```

- [1].madclient通过ZMQ_DEALER模式异步给madbroker发送消息，madbroker通过ZMQ_ROUTER模式异步接收消息
- [2].madbroker担当消息发布者，通过ZMQ_PUB模式发布消息；madserver作为消息订阅者，通过ZMQ_SUB模式订阅消息
- [3].madserver通过ZMQ_DEALER模式异步发消息给madbroker，从madbroker中获取当前消息的快照



