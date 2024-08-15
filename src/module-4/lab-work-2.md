# Лабораторная работа №2

- ## Настройка протокола STP

  - ### LW-SW-1

  ```
  L2-SW-1(config)#spanning-tree vlan 1 root primary

  This bridge is the root

  Bridge ID  Priority    24577  (priority 24576 sys-id-ext 1)
             Address     0c71.d551.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec
  ```

  - ### LW-SW-2

  ```
  L2-SW-2(config)#spanning-tree vlan 1 root secondary

  Cost       4
  Port       1 (GigabitEthernet0/0)

  Bridge ID  Priority    28673  (priority 28672 sys-id-ext 1)
             Address     0c7e.48ca.0000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec
  ```

  - ### Схема сети

  ![Screenshot from 2024-08-15 17-04-06](https://github.com/user-attachments/assets/1425ff26-0b0f-400e-b808-92b6f3cc1dba)

- ## Проверка доступности персональных компьютеров

  - ### PC1

    - To PC2

    ```
    PC1> ping 192.168.1.2

    84 bytes from 192.168.1.2 icmp_seq=1 ttl=64 time=0.637 ms
    84 bytes from 192.168.1.2 icmp_seq=2 ttl=64 time=0.418 ms
    84 bytes from 192.168.1.2 icmp_seq=3 ttl=64 time=0.920 ms
    84 bytes from 192.168.1.2 icmp_seq=4 ttl=64 time=0.580 ms
    84 bytes from 192.168.1.2 icmp_seq=5 ttl=64 time=0.981 ms
    ```

    - To PC3

    ```
    PC1> ping 192.168.2.1

    84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=9.333 ms
    84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=2.423 ms
    84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=11.989 ms
    84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=3.975 ms
    84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=5.666 ms
    ```

    - To PC4

    ```
    PC1> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=11.144 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=7.366 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=6.732 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=8.019 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=7.309 ms
    ```

    - To PC5

    ```
    PC1> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=2.549 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=2.088 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=7.229 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=7.482 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=14.778 ms
    ```

    - To PC6

    ```
    PC1> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=9.611 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=3.815 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=4.567 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=6.477 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=6.627 ms
    ```

  - ### PC2

    - To PC3

    ```
    PC2> ping 192.168.2.1

    84 bytes from 192.168.2.1 icmp_seq=1 ttl=64 time=18.684 ms
    84 bytes from 192.168.2.1 icmp_seq=2 ttl=64 time=14.516 ms
    84 bytes from 192.168.2.1 icmp_seq=3 ttl=64 time=15.761 ms
    84 bytes from 192.168.2.1 icmp_seq=4 ttl=64 time=15.579 ms
    84 bytes from 192.168.2.1 icmp_seq=5 ttl=64 time=15.927 ms
    ```

    - To PC4

    ```
    PC2> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=13.109 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=7.428 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=6.474 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=5.760 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=9.032 ms
    ```

    - To PC5

    ```
    PC2> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=28.926 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=1.431 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=4.684 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=1.948 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=5.895 ms
    ```

    - To PC6

    ```
    PC2> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=21.236 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=1.329 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=5.296 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=1.666 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=9.738 ms
    ```

  - ### PC3

    - To PC4

    ```
    PC3> ping 192.168.2.2

    84 bytes from 192.168.2.2 icmp_seq=1 ttl=64 time=0.669 ms
    84 bytes from 192.168.2.2 icmp_seq=2 ttl=64 time=2.806 ms
    84 bytes from 192.168.2.2 icmp_seq=3 ttl=64 time=7.177 ms
    84 bytes from 192.168.2.2 icmp_seq=4 ttl=64 time=0.680 ms
    84 bytes from 192.168.2.2 icmp_seq=5 ttl=64 time=6.789 ms
    ```

    - To PC5

    ```
    PC3> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=13.787 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=2.895 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=7.819 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=2.381 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=7.184 ms
    ```

    - To PC6

    ```
    PC3> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=10.929 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=6.957 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=7.512 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=1.966 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=12.268 ms
    ```

  - ### PC4

    - To PC5

    ```
    PC4> ping 192.168.3.1

    84 bytes from 192.168.3.1 icmp_seq=1 ttl=64 time=15.582 ms
    84 bytes from 192.168.3.1 icmp_seq=2 ttl=64 time=7.798 ms
    84 bytes from 192.168.3.1 icmp_seq=3 ttl=64 time=12.691 ms
    84 bytes from 192.168.3.1 icmp_seq=4 ttl=64 time=2.948 ms
    84 bytes from 192.168.3.1 icmp_seq=5 ttl=64 time=1.350 ms
    ```

    - To PC6

    ```
    PC4> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=14.132 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=3.531 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=6.322 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=13.398 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=6.513 ms
    ```

  - ### PC5

    - To PC6

    ```
    PC5> ping 192.168.3.2

    84 bytes from 192.168.3.2 icmp_seq=1 ttl=64 time=2.193 ms
    84 bytes from 192.168.3.2 icmp_seq=2 ttl=64 time=7.757 ms
    84 bytes from 192.168.3.2 icmp_seq=3 ttl=64 time=4.090 ms
    84 bytes from 192.168.3.2 icmp_seq=4 ttl=64 time=2.572 ms
    84 bytes from 192.168.3.2 icmp_seq=5 ttl=64 time=7.265 ms
    ```

- ## Show Running Command Outputs

  - ### LW-SW-1

  ```
    Building configuration...

    Current configuration : 5209 bytes
    !
    ! Last configuration change at 15:48:07 UTC Thu Aug 15 2024
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
    interface GigabitEthernet0/0
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/1
     media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/2
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/3
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/0
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/1
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/2
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/3
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

  - ### LW-SW-2

  ```
    Building configuration...

    Current configuration : 5209 bytes
    !
    ! Last configuration change at 15:48:54 UTC Thu Aug 15 2024
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
    interface GigabitEthernet0/0
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/1
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/2
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet0/3
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/0
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/1
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/2
    media-type rj45
    negotiation auto
    !
    interface GigabitEthernet1/3
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
