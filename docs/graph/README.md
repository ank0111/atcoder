# Graph

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

## グラフを作成する

```cpp
void resize(int n)
```

グラフの頂点数を $n$ に設定する。

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

## グラフを取得する

```cpp
vector<vector<int>> graph()
```

グラフを隣接リストの形式で返します。

```cpp
int size()
```

グラフの頂点数を返します。

## 各頂点までの距離を計算する

```cpp
vector<int> dis(int s=0)
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
