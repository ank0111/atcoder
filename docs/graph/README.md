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

## 移動経路を取得する

```cpp
vector<int> prev()
```

直前に実行した [`dis`](#各頂点までの距離を計算する) の計算過程で得られた各頂点の直接の親頂点のリストを返します。

```cpp
vi path(int u, int v)
```

頂点 $u$ から 頂点 $v$ までの最短の移動経路を返します。

条件に合う移動経路が複数あるときはそのうちの $1$ つを返します。

**制約**

- $0 \leq u < n$
- $0 \leq v < n$

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
