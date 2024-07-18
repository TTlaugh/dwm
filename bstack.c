void
bstack(Monitor *m)
{
	unsigned int i, n, w, mh, mx, tx, bw;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (n == 1)
		bw = 0;
	else
		bw = borderpx;
	if (n > m->nmaster)
		mh = m->nmaster ? m->wh * m->mfact : 0;
	else
		mh = m->wh;
	for (i = mx = tx = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - 2*bw, mh - 2*bw + (n > 1 ? gappx : 0), bw, 0);
			if (mx + WIDTH(c) < m->ww)
				mx += WIDTH(c);
		} else {
			w = (m->ww - tx) / (n - i);
			resize(c, m->wx + tx, m->wy + mh, w - 2*bw - (n == 1 ? gappx : 0), m->wh - mh - 2*bw, bw, 0);
			if (tx + WIDTH(c) < m->ww)
				tx += WIDTH(c);
		}
}
