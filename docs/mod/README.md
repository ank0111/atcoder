<script>
MathJax = {
  tex: {
    inlineMath: [['$', '$'], ['\\(', '\\)']]
  },
  svg: {
    fontCache: 'global'
  }
};
</script>
<script type="text/javascript" id="MathJax-script" async
  src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js">
</script>

# Mod

$mod$ 計算をまとめています。

## コンストラクタ

```cpp
Mod mod(int m)
```

$m$ を法とした計算ができる構造体です。

## 累乗を計算する

```cpp
ll pow(ll x,ll n)
```

$x^n$ を $m$ で割った余りを返します。

**計算量**

- $O(\log{n})$

**制約**

- $n \geq 0$

## 順列・組み合わせを計算する

### 階乗

```cpp
ll F(int x)
```

$x!$ を $m$ で割った余りを返します。

```cpp
ll invF(int x)
```

$x!$ の $m$ を法とした逆元を返します。

### 順列

```cpp
ll P(int n,int r)
```

$_n P _r$ （ $n$ 個から重複せずに $r$ 個選ぶ順列数）を $m$ で割った余りを返します。

### 組み合わせ

```cpp
ll C(int n,int r)
```

$_n C _r$ （ $n$ 個から重複せずに $r$ 個選ぶ組み合わせ数）を $m$ で割った余りを返します。

```cpp
ll H(int n,int r)
```

$_n H _r$ （ $n$ 個から重複を許して $r$ 個選ぶ組み合わせ数）を $m$ で割った余りを返します。