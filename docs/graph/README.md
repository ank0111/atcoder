# Graph : vector<vector<int>>

グラフ関連の操作をまとめています。

## コンストラクタ

```cpp
Graph g(int n=0,int m=0,bool d=false)
```

$n$ 頂点のグラフを作成します。

グラフ作成時に、[`load(m, d)`](#loadm) を実行します。

```cpp
Graph g(int n,vector<pair<int,int>> e,bool d=false)
```

$n$ 頂点のグラフを作成します。

グラフ作成時に、[`load(e, d)`](#loade) を実行します。

```cpp
Graph g(vector<vector<int>> v)
```

$2$ 次元ベクトル $v$ を元にグラフを作成します。

## グラフを作成する

```cpp
void resize(int n)
```

グラフの頂点数を $n$ に設定します。

<a id="loadm"></a>

```cpp
void load(int m,bool d=false)
```

標準入力から $u,\ v$ を受け取り、頂点 $u,\ v\ (1-indexed)$ の間に辺を張ることを $m$ 回繰り返します。

$d$ が $true$ のときは、 $u$ から $v$ に向けた辺のみ作成します。

**制約**

- $0 < u \leq n$
- $0 < v \leq n$

<a id="loade"></a>

```cpp
void load(vector<pair<int,int>> e,bool d=false)
```

$e$ の各要素を $u,\ v$ に分割し、頂点 $u,\ v\ (0-indexed)$ の間に辺を張ります。

$d$ が $true$ のときは、 $u$ から $v$ に向けた辺のみ作成します。

**制約**

- $0 \leq u < n$
- $0 \leq v < n$

```cpp
void add_edge(int from,int to)
```

頂点 $from$ から 頂点 $to$ に向けて辺を張ります。

$u,\ v$ は $(0-indexed)$ です。

**制約**

- $0 \leq from < n$
- $0 \leq to < n$

## 各頂点までの距離を計算する

```cpp
vector<int> dis(int s)
```

頂点 $s$ から各頂点までの距離のリストを返します。

**制約**

- $0 \leq s < n$

```cpp
vector<int> prev()
```

直前に実行した [`dis`](#各頂点までの距離を計算する) の計算過程で得られた各頂点の直接の親頂点のリストを返します。

## トポロジカルソート

```cpp
vector<int> tpsort()
```

トポロジカルソートした結果を返します。

閉路は返すリストに含まれません。

## $2$ 部グラフか調べる

```cpp
bool isBG()
```

グラフが $2$ 部グラフであれば $true$ を、そうでないとき $false$ を返します。

```cpp
vector<int> color()
```

直前に実行した [`isBG`](#2-部グラフか調べる) の計算過程で得られた各頂点の色分けリストを返します。

# Tree : Graph

グラフの中でも、木に対する操作をまとめています。

Graph を継承しています。

## コンストラクタ

```cpp
Tree(int n=0)
```

[`Graph(n,n-1)`](#コンストラクタ) を実行します。

```cpp
Tree(vector<vector<int>> t)
```

[`Graph(t)`](#コンストラクタ) を実行します。

## 木の直径を求める

```cpp
tuple<int,int,int> tdia()
```

木の直径 $d$ 、直径の両端 $s,\ t$ を $\lbrace \ d,\ s,\ t\ \rbrace$ の形式で返します。

## ダブリング

```cpp
vector<vector<int>> doubling(int r)
```

$r$ を根とした木のダブリング処理の結果を返します。

`result[i][j]` は頂点 $i$ の $2^j$ 個先の親頂点を表します。

**制約**

- $0 \leq r < n$

```cpp
int lca(int a, int b)
```

直前に実行した [`doubling(r)`](#ダブリング) の結果を利用して、頂点 $a,\ b$ の最小共通祖先を返します。

**制約**

- $0 \leq a < n$
- $0 \leq b < n$

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
