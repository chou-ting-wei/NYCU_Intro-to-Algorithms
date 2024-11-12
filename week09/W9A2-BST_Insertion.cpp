/* probID: W9-A2-Insertion */

void update_size(node *n){
    if(n){
        n->l_sz = n->lc ? n->lc->l_sz + n->lc->r_sz + 1 : 0;
        n->r_sz = n->rc ? n->rc->l_sz + n->rc->r_sz + 1 : 0;
    }
}

node* find_kth(node *root, int k){
    if(!root) return nullptr;
    int left_size = root->l_sz;
    if(k <= left_size){
        return find_kth(root->lc, k);
    }
    else if(k == left_size + 1){
        return root;
    }
    else{
        return find_kth(root->rc, k - left_size -1);
    }
}

node* find_predecessor(node *n){
    if(!n) return nullptr;
    if(n->lc){
        n = n->lc;
        while(n->rc){
            n = n->rc;
        }
        return n;
    }
    while(n->p && n == n->p->lc){
        n = n->p;
    }
    return n->p;
}

node* find_successor(node *n){
    if(!n) return nullptr;
    if(n->rc){
        n = n->rc;
        while(n->lc){
            n = n->lc;
        }
        return n;
    }
    while(n->p && n == n->p->rc){
        n = n->p;
    }
    return n->p;
}

void BST_insert_before(node *r, int pos, node *nde){
    if(!r) return;

    node *target = find_kth(r, pos);
    if(!target){
        return;
    }

    node *pred = find_predecessor(target);

    if(pred){
        nde->p = pred;
        nde->lc = nde->rc = nullptr;
        nde->l_sz = nde->r_sz = 0;
        if(!pred->rc){
            pred->rc = nde;
        }
        else{
            node *current = pred->rc;
            while(current->lc){
                current = current->lc;
            }
            current->lc = nde;
            nde->p = current;
        }
    }
    else{
        nde->p = target->p;
        nde->lc = nde->rc = nullptr;
        nde->l_sz = nde->r_sz = 0;
        if(!target->p){
            nde->p = nullptr;
        }
        else{
            if(target->p->lc == target){
                target->p->lc = nde;
            }
            else{
                target->p->rc = nde;
            }
        }
        nde->lc = target->lc;
        nde->rc = target;
        if(target->lc){
            target->lc->p = nde;
        }
        target->p = nde;
        target->lc = nullptr;
        update_size(target);
    }

    node *current = nde;
    while(current){
        update_size(current);
        current = current->p;
    }
}

void BST_insert_after(node *r, int pos, node *nde){
    if(!r) return;

    node *target = find_kth(r, pos);
    if(!target){
        return;
    }

    node *succ = find_successor(target);

    if(succ){
        nde->p = succ;
        nde->lc = nde->rc = nullptr;
        nde->l_sz = nde->r_sz = 0;
        if(!succ->lc){
            succ->lc = nde;
        }
        else{
            node *current = succ->lc;
            while(current->rc){
                current = current->rc;
            }
            current->rc = nde;
            nde->p = current;
        }
    }
    else{
        nde->p = target->p;
        nde->lc = nde->rc = nullptr;
        nde->l_sz = nde->r_sz = 0;
        if(!target->p){
            nde->p = nullptr;
        }
        else{
            if(target->p->lc == target){
                target->p->lc = nde;
            }
            else{
                target->p->rc = nde;
            }
        }
        nde->rc = target->rc;
        nde->lc = target;
        if(target->rc){
            target->rc->p = nde;
        }
        target->p = nde;
        target->rc = nullptr;
        update_size(target);
    }

    node *current = nde;
    while(current){
        update_size(current);
        current = current->p;
    }
}
