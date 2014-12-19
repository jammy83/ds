//
//  hashTable.h
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#ifndef _hashTable_h
#define _hashTable_h

template<class t_key, class t_record, unsigned long t_val>
class hashTableRecord {
public:
    t_key _key;
    t_val _value;
    t_record* _next; // for chaining keys with the same hash
    //virtual const t_key& giveKey() const = 0;
    t_key giveKey() const { return _key; }
};

template<class t_key, class t_record, unsigned long t_size>
class hashMap {
private:
    t_record* _table[t_size];
    unsigned long _recCount;
    bool remove(t_record* rec, unsigned long bkt);
    
public:
    hashMap() {
        for (unsigned long i = 0; i < t_size; i++) {
            _table[i] = NULL;
        }
        _recCount = 0;
    }
    ~hashMap() {
        for (unsigned long int i = 0; i < t_size; i++) {
            delete _table[i];
        }
        _recCount = 0;
    }
    void insert(t_record* rec);
    t_record* lookup(const t_key& key);
    bool remove(t_record* rec);
    unsigned long count() const {
        return _recCount;
    }
};

template<class t_key, class t_record, unsigned long t_size>
void hashMap<t_key,t_record,t_size>::insert(t_record* rec)
{
    const unsigned long hash = ((unsigned long)rec->giveKey())%t_size;
    rec->_next = _table[hash];
    _table[hash] = rec;
    _recCount++;
    //Note: for linear probling simply find an empty spot
    //by doing (hash+1)%t_size until _table[hash] != NULL && _table[hash]->giveKey() != key
}

template<class t_key, class t_record, unsigned long t_size>
t_record* hashMap<t_key,t_record,t_size>::lookup(const t_key& key)
{
    const unsigned long hash = ((unsigned long)key)%t_size;
    for (t_record* rec = _table[hash]; rec != NULL; rec = rec->_next) {
        if (rec->giveKey() == key) {
            return rec;
        }
    }
    return NULL;
}

template<class t_key, class t_record, unsigned long t_size>
bool hashMap<t_key,t_record,t_size>::remove(t_record* rec)
{
    const unsigned long hash = ((unsigned long)rec->giveKey())%t_size;
    remove(rec, hash);
}

template<class t_key, class t_record, unsigned long t_size>
bool hashMap<t_key,t_record,t_size>::remove(t_record* rec, unsigned long bkt)
{
    if (_table[bkt] == NULL) {
        return false;
    }
    // head is the element to be removed
    if (_table[bkt] == rec) {
        _table[bkt] = rec->_next;
        rec->_next = NULL;
        _recCount--;
        return true;
    }
    t_record* start = _table[bkt];
    while (start->_next != NULL) {
        if (start->_next == rec) {
            start->_next = rec->_next;
            rec->_next = NULL;
            _recCount--;
            return true;
        }
        start = start->_next;
    }
    return false;
}

#endif
