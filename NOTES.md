# 学习笔记

## 2026-08-10：第三视角看不到瞄准 + 他人角色同步瞄准问题

### 问题现象
1. 自己右键瞄准时，其他玩家从第三视角看不到我在瞄准。
2. 自己瞄准时，明明另一个玩家没有瞄准，却看到他同时进入瞄准状态。

### 原因分析
- `bAiming` 的复制链路本身是正确且完整的：客户端 `Local_Aim()` 本地设置 → `Server_Aim()` RPC 通知服务器 → 服务器更新权威副本 → `DOREPLIFETIME_CONDITION(..., COND_SkipOwner)` 复制给其他客户端。
- 真正的 bug 在第三视角动画蓝图 `ABP_ThirdPerson`：它缓存"Shooter Character"时用的是 `GetPlayerPawn`（获取**本地玩家**的 Pawn），而不是 `TryGetPawnOwner`（**动画网格所属**的 Pawn）。
- 结果：每台机器上所有角色的 3P 动画读到的都是"本地玩家自己"的 `bAiming`：
  - 我瞄准 → 本地 `bAiming=true` → 我屏幕上每个角色都进入瞄准姿势（症状 2）。
  - 对方机器同样读他自己的 `bAiming`（false）→ 他看不到我在瞄准（症状 1）。
- 对比：第一视角动画蓝图 `ABP_FirstPerson` 用的是 `TryGetPawnOwner`，所以 1P 正常。

### 修改方案
- 在 `ABP_ThirdPerson` 中把缓存角色节点的 `GetPlayerPawn` 替换为 `TryGetPawnOwner`，再 Cast 成 `ShooterCharacter`。
- C++ 代码无需改动。

### 相关知识点
1. **动画蓝图读取角色数据的正确姿势**：`AnimInstance::TryGetPawnOwner` 返回该动画实例所驱动的网格的拥有 Pawn；`UGameplayStatics::GetPlayerPawn(0)` 永远返回本地 0 号玩家的 Pawn。角色动画（尤其 3P 多人）必须用前者，否则所有角色共享本地玩家状态。
2. **Server RPC 模式**：客户端输入 → 本地立即执行（无延迟手感）→ 同时发 `Server,Reliable` RPC 同步权威状态；服务器在 `_Implementation` 里执行相同逻辑。
3. **复制条件 COND_SkipOwner**：属性只复制给非拥有者，拥有者用自己的本地值。适合"本地已有即时状态、只需同步给他人"的变量（如瞄准/开火状态），可减少带宽。
4. **动画蓝图读取复制属性无需 OnRep**：纯数据读取（如 ABP 每帧取 `bAiming`）不需要 `ReplicatedUsing`；只有需要在状态变化时执行逻辑（如换枪挂接）才需要 `ReplicatedUsing` + `OnRep`。
5. **监听服务器双开测试要点**：每个 PIE 窗口内"本地玩家 0"是不同的角色，非常适合验证此类复制与本地状态错位的问题。
