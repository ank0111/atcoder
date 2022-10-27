# PersistentStack<T=int>

永続スタックです。

各操作時点でのスタックの状態を保持することができます。


## top

```cpp
T top() const
```

先頭の要素を返します。

**制約**

- $n \geq 1$

## empty

```cpp
bool empty() const
```

永続スタックが空かどうかを返します。

## size

```cpp
size_t size() const
```

永続スタックの要素数を返します。

## push

```cpp
PersistentStack push (const T &v) const
```

永続スタックに要素 $v$ を追加します。

追加後の永続スタックを返します。

## pop

```cpp
PersistentStack pop() const
```

永続スタックの先頭の要素を削除します。

**制約**

- $n \geq 1$

# PersistentArray<T=int,size_t SIZE=10>

永続配列です。

各操作時点での配列の状態を保持することができます。


## コンストラクタ

```cpp
PersistentArray(size_t n=0)
```

要素数 $n$ の永続配列を生成します。

```cpp
PersistentArray(const vector<T> &src)
```

配列 $src$ を元に永続配列を生成します。

## size

```cpp
size_t size() const
```

永続配列の要素数を返します。

## resize

```cpp
PersistentArray resize(size_t n) const
```

永続配列の要素数を $n$ に再設定します。

再設定後の永続スタックを返します。

## destructive_set

```cpp
void destructive_set(size_t i, const T &v)
```

永続配列の $i$ 番目の要素を $v$ に破壊的に更新します。

**制約**

- $i < n$

## set

```cpp
PersistentArray set(size_t i,const T &v) const
```

永続配列の $i$ 番目の要素を $v$ に更新します。

更新後の永続配列を返します。

**制約**

- $i < n$

## get

```cpp
T get(size_t i) const
```

永続配列の $i$ 番目の要素を返します。

**制約**

- $i < n$

## push

```cpp
PersistentArray push(const T &v) const
```

永続配列の末尾に要素 $v$ を追加します。

更新後の永続配列を返します。

## pop

```cpp
PersistentArray pop() const
```

永続配列の末尾の要素を削除します。

更新後の永続配列を返します。
