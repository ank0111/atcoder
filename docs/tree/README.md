# Tree : Graph

木に対する操作をまとめています。

[Graph](../graph) を継承しています。

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
tuple<int,int,int> dia()
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

```cpp
int dis(int u, int v)
```

直前に実行した [`doubling(r)`](#ダブリング) の結果を利用して、頂点 $u,\ v$ 間の距離を返します。

**制約**

- $0 \leq u < n$
- $0 \leq v < n$

## 頂点の並び順を求める

```cpp
int preorder(int r)
```

頂点 $r$ を根としたときの各頂点の行きがけ順リストを返します。

**制約**

- $0 \leq r < n$

```cpp
int postorder(int r)
```

頂点 $r$ を根としたときの各頂点の帰りがけ順リストを返します。

**制約**

- $0 \leq r < n$
