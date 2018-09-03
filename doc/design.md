# Fig Design

## Key Abstractions / Interfaces

### IFigTree

The main abstraction with which to interact with a configuration. Encapasulates the logical tree structure of a configuration.

Responsible for traversing the logical configuration structure and retrieving config values.

#### IFigTree Methods

- `bool Load()` Loads the configuration data from the data source.
- `bool Save()` Saves the configuration data to the data source (if supported).
- `IFigNode Get(IFigKey)` Returns the `IFigNode` associated with the given `IFigKey`.
- `IFigNodeIterator Find(IFigQuery)` Returns an `IFigNodeIterator` that iterates over the results of the `IFigQuery`.

### IFigNode

Represents a single node within the logical configuration tree encapsulated by an IFigTree. An IFigNode has 0 or more children, each of which is also an IFigNode. Separately, an IFigNode has 0 or 1 value, corresponding to the value of a configuration property.

#### IFigNode Methods

- `IFigNodeIterator Children()` Returns an `IFigNodeIterator` that iterates over the immediate children of the `IFigNode`.
- `IFigNode Get(IFigKey)` Returns the child `IFigNode` associated with the given `IFigKey`.
- `IFigNodeIterator Find(IFigQuery)` Searches the children of the `IFigNode` for any having keys that match the given `IFigQuery` and returns an `IFigNodeIterator` that iterates over the results.
- `IFigKey Key()` Returns the `IFigKey` that identifies the `IFigNode`.
- `IFigKey FullKey()` Returns the fully-qualified `IFigKey` that uniquely locates the `IFigNode` in the tree.
- `bool HasValue()` Returns true if the `IFigNode` has a value, false otherwise.
- `IFigValue Value()` Returns the value of the `IFigNode`.
- `bool HasAttributes()` Returns true if the `IFigNode` has attributes (i.e. metadata) that describe the node. NOTE: mainly to support XML attributes, but abstractly.
- `IFigValueIterator Attributes()` Returns an `IFigValueIterator` that iterates over the `IFigNode`s attributes.
- `bool Valid()` Returns true if the `IFigNode` represents a valid node in the configuration tree.

### IFigValue

Encapsulates a single configuration property or attribute value in its native form, and provides access to the value converted to one or more alternate data types.

#### IFigValue Methods

- `template<typename T> T Get()` Returns the value as type `T` if there is an automatic conversion to `T` available.
- `template<typename T> T Get(IFigConverter<T>)` Returns the value as type `T` using the given conversion function.

### IDataSourceProvider

Responsible for retrieving binary/unstructured configuration data from a specific type of data source. Possible examples include: file system, HTTP server, MySQL database, etc.

#### IDataSourceProvider Methods

- `bool Load()` Retrieves data from the data source. Returns true if successful, false otherwise.
- `IDataStream Data()` Returns a data stream providing access to the data retrieved from the data source.

### IDataStoreProvider

Responsible for storing binary/unstructured configuration data into a specific type of data store. Possible examples include: file system, HTTP server, MySQL database, etc.

#### IDataStoreProvider Methods

- `bool Save()` Stores data into the data store. Returns true if successful, false otherwise.
- `void Data(IDataStream)` Accepts a data stream providing access to the data to be stored in the data store.

### IDataFormatProvider

Responsible for parsing binary/unstructured configuration data into a logical data structure usable by consumers.

#### IDataFormatProvider Methods

- `bool Unserialize()`
- `bool Serialize()`

### IVariableProvider

Responsible for providing access to key/value data to be used in dynamic substitution of variables for tokens embedded in the binary/unstructured configuration data.

#### IVariableProvider Methods

- `IVariableIterator Variables()` Returns an iterator over the collection of variable key/value data.

### IFigKey

Abstraction for describing a unique identifier of an IFigNode.

#### IFigKey Methods

- `std::wstring Uri()` Returns the key formatted as a URI.
- `uint64_t Hash()` Returns a stable hash of the key to be used in hash maps.

## Supporting Abstractions

### InitOnFirstUsePolicy

A mixin or policy template class that supports deferred initialization of the host class by calling a private `Init()` method and tracking whether initialization succeeded.

#### InitOnFirstUsePolicy Methods

- `bool Init()` (not public) Initializes the object using internal state set in the initial call to the ctor. Returns true on success, false otherwise. Idempotent: subsequent calls are no-ops that return the result of `Valid()`.
- `bool Valid()` Returns true if `Init()` succeeded, false otherwise.
- `void SetValid(bool)` (not public) Sets the internal initialization state to the given argument; true if successful, false otherwise.

### Result<T, E>

Abstraction for returning a result value or error value from a function. Example:

    Result<int, Err> foo(bool good) {
        if (good)
            return 1;
        return Err("bad");
    }

    auto f = foo(true);
    if (f) 
        cout << f.value();
    else
        cout << f.error();

See: [Exceptions vs expected: Let's find a compromise](https://foonathan.net/blog/2017/12/04/exceptions-vs-expected.html) for more information.
