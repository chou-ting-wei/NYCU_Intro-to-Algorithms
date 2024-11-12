/* probID: W9-A1-Rotation */

node *rotate_dir(node *r, bool dir){
    if (!r) return nullptr;

    node *tmp = dir ? r->lc : r->rc;

    tmp->p = r->p;
    if (r->p) {
        if (r->p->lc == r) {
            r->p->lc = tmp;
        }
        else {
            r->p->rc = tmp;
        }
    }

    r->p = tmp;
    
    if(dir){
        r->lc = tmp->rc;
        if(tmp->rc){
            tmp->rc->p = r;
        }
        r->l_sz = tmp->r_sz;
        tmp->rc = r;
        tmp->r_sz = r->l_sz + r->r_sz + 1;
    }
    else{
        r->rc = tmp->lc;
        if(tmp->lc){
            tmp->lc->p = r;
        }
        r->r_sz = tmp->l_sz;
        tmp->lc = r;
        tmp->l_sz = r->l_sz + r->r_sz + 1;
    }
    return tmp;
}