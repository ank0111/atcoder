# CGraph : vector<vector<pair<int, ll>>>

重み付きグラフ関連の操作をまとめています。

## コンストラクタ

```cpp
CGraph g(int n=0,int m=0,bool d=false)
```

$n$ 頂点の重み付きグラフを作成します。

グラフ作成時に、[`load(m, d)`](#loadmc) を実行します。

```cpp
CGraph g(int n,vector<tuple<int,int,ll>> e,bool d=false)
```

$n$ 頂点の重み付きグラフを作成します。

グラフ作成時に、[`load(e, d)`](#loadec) を実行します。

```cpp
CGraph g(vector<vector<pair<int, ll>>> v)
```

$2$ 次元ベクトル $v$ を元に重み付きグラフを作成します。

## グラフを作成する

```cpp
void resize(int n)
```

グラフの頂点数を $n$ に設定します。

<a id="loadmc"></a>

```cpp
void load(int m,bool d=false)
```

標準入力から $u,\ v,\ c$ を受け取り、頂点 $u,\ v\ (1-indexed)$ の間に重み $c$ の辺を張ることを $m$ 回繰り返します。

$d$ が $true$ のときは、 $u$ から $v$ に向けた辺のみ作成します。

**制約**

- $0 < u \leq n$
- $0 < v \leq n$

<a id="loadec"></a>

```cpp
void load(vector<tuple<int,int,ll>> e,bool d=false)
```

$e$ の各要素を $u,\ v,\ c$ に分割し、頂点 $u,\ v\ (0-indexed)$ の間に重み $c$ の辺を張ります。

$d$ が $true$ のときは、 $u$ から $v$ に向けた辺のみ作成します。

**制約**

- $0 \leq u < n$
- $0 \leq v < n$

```cpp
void add_edge(int from,int to,ll c)
```

頂点 $from$ から 頂点 $to$ に向けて重み $c$ の辺を張ります。

$u,\ v$ は $(0-indexed)$ です。

**制約**

- $0 \leq from < n$
- $0 \leq to < n$

## 各頂点までの距離を計算する

```cpp
vector<ll> dijk(int s)
```

頂点 $s$ から各頂点までの最小コストのリストを返します。

重みが負の辺がある場合は正しい答えを返しません。

**計算量**

- $O(\ (n*m)\log{m}\ )$

**制約**

- $0 \leq s < n$
- 全ての辺の重みが $0$ 以上

```cpp
vector<ll> bellfo(int s)
```

頂点 $s$ から各頂点までの最小コストのリストを返します。

重みが負の辺がある場合も正しい答えを返します。

**計算量**

- $O(\ n*m\ )$

**制約**

- $0 \leq s < n$

```cpp
vector<int> prev()
```

直前に実行した [`dijk`](#各頂点までの距離を計算する) または [`bellfo`](#各頂点までの距離を計算する) の計算過程で得られた各頂点の直接の親頂点のリストを返します。
