#pragma once

bool myHashSetAdd (MyHashSet *const in_hSet, int key);
bool myHashSetContains (MyHashSet *in_hSet, int data);
bool myHashSetFree (MyHashSet *in_hSet);
bool myHashSetRemove (MyHashSet *hSet, int data);
