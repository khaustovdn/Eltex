# Лабораторная работа №3

- ## Настройка на коммутаторах протокола LACP агрегирования каналов технологии EtherChannel

  - ### L2-SW-1

  ```
  L2-SW-1(config)#int range g0/0-1
  L2-SW-1(config-if-range)#shut
  L2-SW-1(config-if-range)#channel-group 1 mode active
  L2-SW-1(config-if-range)#no shut

  L2-SW-1(config)#int range g0/2-3
  L2-SW-1(config-if-range)#shut
  L2-SW-1(config-if-range)#channel-group 2 mode active
  L2-SW-1(config-if-range)#no shut

  L2-SW-1(config)#int range g1/0-1
  L2-SW-1(config-if-range)#shut
  L2-SW-1(config-if-range)#channel-group 3 mode active
  L2-SW-1(config-if-range)#no shut

  L2-SW-1(config)#int range g1/2-3
  L2-SW-1(config-if-range)#shut
  L2-SW-1(config-if-range)#channel-group 4 mode active
  L2-SW-1(config-if-range)#no shut

  L2-SW-1(config)#int g2/0
  L2-SW-1(config-if)#shut
  L2-SW-1(config-if)#channel-group 4 mode active
  L2-SW-1(config-if)#no shut
  ```

  ```
  L2-SW-1#sh int stats

  Port-channel1
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        669      60232          0          0
             Route cache          0          0          0          0
                   Total        669      60232          0          0
  Port-channel2
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        721      63124          0          0
             Route cache          0          0          0          0
                   Total        721      63124          0          0
  Port-channel3
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        666      60264          0          0
             Route cache          0          0          0          0
                   Total        666      60264          0          0
  Port-channel4
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        828      81255          0          0
             Route cache          0          0          0          0
                   Total        828      81255          0          0
  ```

  ```
  L2-SW-1#sh sp

  VLAN0001
    Spanning tree enabled protocol ieee
    Root ID    Priority    24577
             Address     0cec.7252.0000
             This bridge is the root
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

    Bridge ID  Priority    24577  (priority 24576 sys-id-ext 1)
             Address     0cec.7252.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

  Interface           Role Sts Cost      Prio.Nbr Type
  ------------------- ---- --- --------- -------- --------------------------------
  Po4                 Desg FWD 4         128.65   Shr
  Po3                 Desg FWD 4         128.66   Shr
  Po2                 Desg FWD 3         128.67   Shr
  Po1                 Desg FWD 3         128.68   Shr
  ```

  - ### L2-SW-2

  ```
  L2-SW-2(config)#int range g0/0-2
  L2-SW-2(config-if-range)#shut
  L2-SW-2(config-if-range)#channel-group 4 mode passive
  L2-SW-2(config-if-range)#no shut

  L2-SW-2(config)#int g0/3
  L2-SW-2(config-if)#shut
  L2-SW-2(config-if)#channel-group 5 mode active
  L2-SW-2(config-if)#no shut

  L2-SW-2(config)#int g1/0
  L2-SW-2(config-if)#shut
  L2-SW-2(config-if)#channel-group 5 mode active
  L2-SW-2(config-if)#no shut

  L2-SW-2(config)#int range g1/1-2
  L2-SW-2(config-if-range)#shut
  L2-SW-2(config-if-range)#channel-group 6 mode active
  L2-SW-2(config-if-range)#no shut

  L2-SW-2(config)#int g1/3
  L2-SW-2(config-if)#shut
  L2-SW-2(config-if)#channel-group 7 mode active
  L2-SW-2(config-if)#no shut

  L2-SW-2(config)#int g2/0
  L2-SW-2(config-if)#shut
  L2-SW-2(config-if)#channel-group 7 mode active
  L2-SW-2(config-if)#no shut
  ```

  ```
  L2-SW-2#sh int stats

  Port-channel7
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1230      90143          0          0
             Route cache          0          0          0          0
                   Total       1230      90143          0          0
  Port-channel6
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1317      94939          0          0
             Route cache          0          0          0          0
                   Total       1317      94939          0          0
  Port-channel5
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1267      92102          0          0
             Route cache          0          0          0          0
                   Total       1267      92102          0          0
  Port-channel4
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1493     114968          0          0
             Route cache          0          0          0          0
                   Total       1493     114968          0          0
  ```

  ```
  L2-SW-2#sh sp

  VLAN0001
    Spanning tree enabled protocol ieee
    Root ID    Priority    24577
             Address     0cec.7252.0000
             Cost        4
             Port        65 (Port-channel4)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

    Bridge ID  Priority    28673  (priority 28672 sys-id-ext 1)
             Address     0ca9.270d.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

  Interface           Role Sts Cost      Prio.Nbr Type
  ------------------- ---- --- --------- -------- --------------------------------
  Po4                 Root FWD 4         128.65   Shr
  Po5                 Altn BLK 3         128.66   Shr
  Po6                 Altn BLK 3         128.67   Shr
  Po7                 Altn BLK 3         128.68   Shr
  ```

  - ### L2-SW-3

  ```
  L2-SW-3(config)#int range g0/0-1
  L2-SW-3(config-if-range)#shut
  L2-SW-3(config-if-range)#channel-group 1 mode passive
  L2-SW-3(config-if-range)#no shut

  L2-SW-3(config)#int range g0/2-3
  L2-SW-3(config-if-range)#shut
  L2-SW-3(config-if-range)#channel-group 7 mode passive
  L2-SW-3(config-if-range)#no shut
  ```

  ```
  L2-SW-3#sh int stats

  Port-channel1
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1416      98124          0          0
             Route cache          0          0          0          0
                   Total       1416      98124          0          0
  Port-channel7
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        921      72604          0          0
             Route cache          0          0          0          0
                   Total        921      72604          0          0
  ```

  ```
  L2-SW-3#sh sp

  VLAN0001
    Spanning tree enabled protocol ieee
    Root ID    Priority    24577
             Address     0cec.7252.0000
             Cost        3
             Port        66 (Port-channel1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

    Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     0cec.7d98.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

  Interface           Role Sts Cost      Prio.Nbr Type
  ------------------- ---- --- --------- -------- --------------------------------
  Gi1/0               Desg FWD 4         128.5    Shr
  Gi1/1               Desg FWD 4         128.6    Shr
  Po7                 Desg FWD 3         128.65   Shr
  Po1                 Root FWD 3         128.66   Shr
  ```

  - ### L2-SW-4

  ```
  L2-SW-4(config)#int range g0/0-1
  L2-SW-4(config-if-range)#shut
  L2-SW-4(config-if-range)#channel-group 2 mode passive
  L2-SW-4(config-if-range)#no shut

  L2-SW-4(config)#int range g0/2-3
  L2-SW-4(config-if-range)#shut
  L2-SW-4(config-if-range)#channel-group 6 mode passive
  L2-SW-4(config-if-range)#no shut
  ```

  ```
  L2-SW-4#sh int stats

  Port-channel2
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1356      94911          0          0
             Route cache          0          0          0          0
                   Total       1356      94911          0          0
  Port-channel6
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        839      67612          0          0
             Route cache          0          0          0          0
                   Total        839      67612          0          0
  ```

  ```
  L2-SW-4#sh sp

  VLAN0001
    Spanning tree enabled protocol ieee
    Root ID    Priority    24577
             Address     0cec.7252.0000
             Cost        3
             Port        66 (Port-channel2)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

    Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     0c2f.bdc2.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

  Interface           Role Sts Cost      Prio.Nbr Type
  ------------------- ---- --- --------- -------- --------------------------------
  Gi1/0               Desg FWD 4         128.5    Shr
  Gi1/1               Desg FWD 4         128.6    Shr
  Po6                 Desg FWD 3         128.65   Shr
  Po2                 Root FWD 3         128.66   Shr
  ```

  - ### L2-SW-5

  ```
  L2-SW-5(config)#int range g0/0-1
  L2-SW-5(config-if-range)#shut
  L2-SW-5(config-if-range)#channel-group 3 mode passive
  L2-SW-5(config-if-range)#no shut

  L2-SW-5(config)#int range g0/2-3
  L2-SW-5(config-if-range)#shut
  L2-SW-5(config-if-range)#channel-group 5 mode passive
  L2-SW-5(config-if-range)#no shut
  ```

  ```
  L2-SW-5#sh int stats

  Port-channel3
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor       1379      95318          0          0
             Route cache          0          0          0          0
                   Total       1379      95318          0          0
  Port-channel5
          Switching path    Pkts In   Chars In   Pkts Out  Chars Out
               Processor        885      69935          0          0
             Route cache          0          0          0          0
                   Total        885      69935          0          0
  ```

  ```
  L2-SW-5#sh sp

  VLAN0001
    Spanning tree enabled protocol ieee
    Root ID    Priority    24577
             Address     0cec.7252.0000
             Cost        3
             Port        66 (Port-channel3)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

    Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     0c90.df13.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

  Interface           Role Sts Cost      Prio.Nbr Type
  ------------------- ---- --- --------- -------- --------------------------------
  Gi1/0               Desg FWD 4         128.5    Shr
  Gi1/1               Desg FWD 4         128.6    Shr
  Po5                 Desg FWD 3         128.65   Shr
  Po3                 Root FWD 3         128.66   Shr
  ```

  - ### Схема сети

  ![1](https://github.com/user-attachments/assets/afa2bdbe-0ff5-4336-95b9-4da6d4202a79)

- ## Проверка доступности персональных компьютеров

  - ### PC1

    - To PC2

    ```
    PC1> ping 192.168.1.2

    84 bytes from 192.168.1.2 icmp_seq=1 ttl=64 time=1.620 ms
    84 bytes from 192.168.1.2 icmp_seq=2 ttl=64 time=10.424 ms
    84 bytes from 192.168.1.2 icmp_seq=3 ttl=64 time=2.398 ms
    84 bytes from 192.168.1.2 icmp_seq=4 ttl=64 time=6.965 ms
    84 bytes from 192.168.1.2 icmp_seq=5 ttl=64 time=2.375 ms
    ```

    - To PC3

    ```
    PC1> ping 192.168.2.1

    84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=7.791 ms
    84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=9.264 ms
    84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=5.230 ms
    84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=13.775 ms
    84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=8.563 ms
    ```

    - To PC4

    ```
    PC1> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=9.666 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=2.110 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=5.384 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=6.931 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=7.417 ms
    ```

    - To PC5

    ```
    PC1> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=5.403 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=9.254 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=5.658 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=8.754 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.274 ms
    ```

    - To PC6

    ```
    PC1> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=8.640 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=12.778 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=4.852 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=3.326 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=10.043 ms
    ```

  - ### PC2

    - To PC3

    ```
    PC2> ping 192.168.2.1

    84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=8.649 ms
    84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=4.912 ms
    84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=9.386 ms
    84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=7.370 ms
    84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=6.053 ms
    ```

    - To PC4

    ```
    PC2> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=15.300 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=1.889 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=4.917 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=7.351 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=15.628 ms
    ```

    - To PC5

    ```
    PC2> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=6.011 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=8.439 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=6.778 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=4.606 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=1.966 ms
    ```

    - To PC6

    ```
    PC2> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.502 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=14.782 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=8.519 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.828 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.183 ms
    ```

  - ### PC3

    - To PC4

    ```
    PC3> ping 192.168.2.2

    192.168.2.2 icmp_seq=1 timeout
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=4.866 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=7.331 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=1.012 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=4.372 ms
    ```

    - To PC5

    ```
    PC3> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=12.586 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=2.243 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=7.451 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=3.524 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=13.593 ms
    ```

    - To PC6

    ```
    PC3> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=3.276 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=10.136 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=7.496 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.775 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=9.741 ms
    ```

  - ### PC4

    - To PC5

    ```
    PC4> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=47.457 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=7.816 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=6.483 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=1.836 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=8.011 ms
    ```

    - To PC6

    ```
    PC4> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=9.896 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=1.635 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=4.730 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=14.912 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=6.652 ms
    ```

  - ### PC5

    - To PC6

    ```
    PC5> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=2.154 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=1.757 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=0.757 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=2.026 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=3.767 ms
    ```

- ## Show Running Command Outputs

  - ### L2-SW-1

  ```
    Current configuration : 5688 bytes
    !
    ! Last configuration change at 14:53:15 UTC Sat Aug 17 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-1
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    spanning-tree vlan 1 priority 24576
    !
    vlan internal allocation policy ascending
    !
    vlan 100
      name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel4
      switchport
    !
    interface Port-channel3
      switchport
    !
    interface Port-channel2
      switchport
    !
    interface Port-channel1
      switchport
    !
    interface GigabitEthernet0/0
      media-type rj45
      negotiation auto
      channel-group 1 mode active
    !
    interface GigabitEthernet0/1
      media-type rj45
      negotiation auto
      channel-group 1 mode active
    !
    interface GigabitEthernet0/2
      media-type rj45
      negotiation auto
      channel-group 2 mode active
    !
    interface GigabitEthernet0/3
      media-type rj45
      negotiation auto
      channel-group 2 mode active
    !
    interface GigabitEthernet1/0
      media-type rj45
      negotiation auto
      channel-group 3 mode active
    !
    interface GigabitEthernet1/1
      media-type rj45
      negotiation auto
      channel-group 3 mode active
    !
    interface GigabitEthernet1/2
      media-type rj45
      negotiation auto
      channel-group 4 mode active
    !
    interface GigabitEthernet1/3
      media-type rj45
      negotiation auto
      channel-group 4 mode active
    !
    interface GigabitEthernet2/0
      media-type rj45
      negotiation auto
      channel-group 4 mode active
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
  ```

  - ### L2-SW-2

  ```
    Current configuration : 5691 bytes
    !
    ! Last configuration change at 14:53:15 UTC Sat Aug 17 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-2
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    spanning-tree vlan 1 priority 28672
    !
    vlan internal allocation policy ascending
    !
    vlan 100
      name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel4
      switchport
    !
    interface Port-channel5
      switchport
    !
    interface Port-channel6
      switchport
    !
    interface Port-channel7
      switchport
    !
    interface GigabitEthernet0/0
      media-type rj45
      negotiation auto
      channel-group 4 mode passive
    !
    interface GigabitEthernet0/1
      media-type rj45
      negotiation auto
      channel-group 4 mode passive
    !
    interface GigabitEthernet0/2
      media-type rj45
      negotiation auto
      channel-group 4 mode passive
    !
    interface GigabitEthernet0/3
      media-type rj45
      negotiation auto
      channel-group 5 mode active
    !
    interface GigabitEthernet1/0
      media-type rj45
      negotiation auto
      channel-group 5 mode active
    !
    interface GigabitEthernet1/1
      media-type rj45
      negotiation auto
      channel-group 6 mode active
    !
    interface GigabitEthernet1/2
      media-type rj45
    negotiation auto
      channel-group 6 mode active
    !
    interface GigabitEthernet1/3
      media-type rj45
      negotiation auto
      channel-group 7 mode active
    !
    interface GigabitEthernet2/0
      media-type rj45
      negotiation auto
      channel-group 7 mode active
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
  ```

  - ### L2-SW-3

  ```
    Current configuration : 5235 bytes
    !
    ! Last configuration change at 14:53:14 UTC Sat Aug 17 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-3
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
      name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel1
      switchport
    !
    interface Port-channel7
      switchport
    !
    interface GigabitEthernet0/0
      media-type rj45
      negotiation auto
      channel-group 1 mode passive
    !
    interface GigabitEthernet0/1
      media-type rj45
      negotiation auto
      channel-group 1 mode passive
    !
    interface GigabitEthernet0/2
      media-type rj45
      negotiation auto
      channel-group 7 mode passive
    !
    interface GigabitEthernet0/3
      media-type rj45
      negotiation auto
      channel-group 7 mode passive
    !
    interface GigabitEthernet1/0
      media-type rj45
      negotiation auto
    !
    interface GigabitEthernet1/1
      media-type rj45
      negotiation auto
    !
    ip forward-protocol nd
    !
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
  ```

  - ### L2-SW-4

  ```
    Current configuration : 5235 bytes
    !
    ! Last configuration change at 14:53:15 UTC Sat Aug 17 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-4
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
      name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel2
      switchport
    !  
    interface Port-channel6
      switchport
    !  
    interface GigabitEthernet0/0
      media-type rj45
      negotiation auto
      channel-group 2 mode passive
    !  
    interface GigabitEthernet0/1
      media-type rj45
      negotiation auto
      channel-group 2 mode passive
    !  
    interface GigabitEthernet0/2
      media-type rj45
      negotiation auto
      channel-group 6 mode passive
    !  
    interface GigabitEthernet0/3
      media-type rj45
      negotiation auto
      channel-group 6 mode passive
    !  
    interface GigabitEthernet1/0
      media-type rj45
      negotiation auto
    !  
    interface GigabitEthernet1/1
      media-type rj45
      negotiation auto
    !  
    ip forward-protocol nd
    !  
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
  ```

  - ### L2-SW-5

  ```
    Current configuration : 5235 bytes
    !
    ! Last configuration change at 14:53:14 UTC Sat Aug 17 2024
    !
    version 15.0
    service timestamps debug datetime msec
    service timestamps log datetime msec
    no service password-encryption
    service compress-config
    !
    hostname L2-SW-5
    !
    boot-start-marker
    boot-end-marker
    !
    !
    !
    no aaa new-model
    !
    !
    !
    vtp domain CISCO-vIOS
    vtp mode transparent
    !
    !
    !
    ip cef
    no ipv6 cef
    !
    !
    !
    spanning-tree mode pvst
    spanning-tree extend system-id
    !
    vlan internal allocation policy ascending
    !
    vlan 100
      name VLAN100
    !
    vlan 200,300
    !
    !
    !
    interface Port-channel3
      switchport
    !  
    interface Port-channel5
      switchport
    !  
    interface GigabitEthernet0/0
      media-type rj45
      negotiation auto
      channel-group 3 mode passive
    !  
    interface GigabitEthernet0/1
      media-type rj45
      negotiation auto
      channel-group 3 mode passive
    !  
    interface GigabitEthernet0/2
      media-type rj45
      negotiation auto
      channel-group 5 mode passive
    !  
    interface GigabitEthernet0/3
      media-type rj45
      negotiation auto
      channel-group 5 mode passive
    !  
    interface GigabitEthernet1/0
      media-type rj45
      negotiation auto
    !  
    interface GigabitEthernet1/1
      media-type rj45
      negotiation auto
    !  
    ip forward-protocol nd
    !  
    no ip http server
    no ip http secure-server
    !
    !
    !
    line con 0
    line aux 0
    line vty 0 4
    line vty 5 15
    !
    !
    end
  ```
