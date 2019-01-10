#include "Mesh.h"

template<class T>
inline void Mesh<T>::Append(vector<T>& vertices, vector<uint>& indices)
{
	AppendVertices(vertices);
	AppendIndices(indices);
}

template<class T>
inline void Mesh<T>::Append(const uint & vertexOffset, const uint & vertexCount, const uint & indexOffset, const uint & indexCount, vector<T>& vertices, vector<uint>& indices)
{
	AppendVertices(vertexOffset, vertexCount, vertices);
	AppendIndices(indexOffset, indexCount, indices);
}

template<class T>
inline void Mesh<T>::AppendVertices(vector<T>& vertices)
{
	vertices = this->vertices;
	//vertices.assign(this->vertices.begin(), this->vertices.end());
}

template<class T>
inline void Mesh<T>::AppendVertices(const uint & offset, const uint & count, vector<T>& vertices)
{
	auto first = this->vertices.begin() + offset;
	auto last = this->vertices.begin() + offset + count;

	vertices.assign(first, last);
}

template<class T>
inline void Mesh<T>::AppendIndices(vector<uint>& indices)
{
	indices = this->indices;
}

template<class T>
inline void Mesh<T>::AppendIndices(const uint & offset, const uint & count, vector<uint>& indices)
{
	auto first = this->indices.begin() + offset;
	auto last = this->indices.begin() + offset + count;

	indices.assign(first, last);
}

template<class T>
inline void Mesh<T>::Clear()
{
	this->indices.clear();
	this->indices.shrink_to_fit();

	this->vertices.clear();
	this->vertices.shrink_to_fit();
}

template<class T>
inline void Mesh<T>::AddVertex(const T & vertex)
{
	this->vertices.emplace_back(vertex);
}

template<class T>
inline void Mesh<T>::AddVertices(const vector<T>& vertices)
{
	this->vertices.insert
	(
		this->vertices.end(),
		vertices.begin(),
		vertices.end()
	);
}

template<class T>
inline void Mesh<T>::SetVertices(const vector<T>& vertices)
{
	Clear();
	this->vertices.assign(vertices.begin(), vertices.end());
}

template<class T>
inline void Mesh<T>::AddIndex(const uint & index)
{
	this->indices.emplace_back(index);
}

template<class T>
inline void Mesh<T>::AddIndices(const vector<uint>& indices)
{
	this->indices.insert
	(
		this->indices.end(),
		indices.begin(),
		indices.end()
	);
}

template<class T>
inline void Mesh<T>::SetIndices(const vector<uint>& indices)
{
	Clear();
	this->indices.assign(indices.begin(), indices.end());
}
