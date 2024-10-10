class Hypergraph:
    def __init__(self, vars: list[int]):
        self.vars = vars
        self.edges: dict[frozenset[int], int] = dict()  # edges with weights

    def add_edge(self, edge):
        edge = frozenset(edge)
        for var in edge:
            # if var not in self.vars:
            # self.vars.append(var)
            assert var in self.vars
        if edge in self.edges:
            self.edges[edge] += 1
        else:
            self.edges[edge] = 1

    def compute_total_span(self, ordering_index: dict[int, int]) -> int:
        """
        Compute the total span w.r.t. the given ordering (a mapping from variable IDs to their index in the ordering).

        The total span is the sum of the span of each edge, which is defined as the difference of the largest and smallest variable index in the ordering among all variables in the edge.
        """
        total_span = 0
        for edge in self.edges:
            var_indices = [ordering_index[v] for v in edge]
            span = max(var_indices) - min(var_indices)
            total_span += span
            # print("edge:", edge, "span:", span)
        return total_span

    def get_var_to_edge(self) -> dict[int, list[frozenset[int]]]:
        """
        A mapping from the hypergraph's variables to a list of the hyperedges in which they appear.
        """
        var2edge = {var: [] for var in self.vars}
        for edge in self.edges:
            for var in edge:
                var2edge[var].append(edge)
        return var2edge

    def compute_force_ordering(self, k=0) -> list[int]:
        """
        Compute a variable ordering using the FORCE algorithm.

        `k` is the maximum number of iterations for positive values of `k`.
        Use `k=0` (default) for unbounded iteration.
        """
        num_vars = len(self.vars)
        var2edge = self.get_var_to_edge()

        # initial ordering
        ordering = self.vars
        ordering_index = {ordering[i]: i for i in range(num_vars)}
        span = self.compute_total_span(ordering_index)
        # print("span:", span)

        best_ordering = ordering
        best_span = span

        i = 1
        while i != k:
            # compute center of gravity (cog) for each clause
            cog = dict()
            for edge in self.edges:
                cog[edge] = sum([ordering_index[v] for v in edge]) / len(edge)

            # compute new var locations and the new ordering
            location = dict()
            for var in ordering:
                var_edges = var2edge[var]
                if len(var_edges) > 0:
                    location[var] = sum([cog[e] for e in var_edges]) / len(var_edges)
                else:
                    location[var] = 0
            new_ordering = sorted(
                ordering,
                key=lambda v: location[v],
            )

            # terminate if ordering is unchanged
            if new_ordering == ordering:
                # print("ordering unchanged")
                # print("span:", span)
                # print("best span:", best_span, f"(-{(span-best_span)*100/span:.2}%)")
                break
            new_ordering_index = {new_ordering[i]: i for i in range(num_vars)}
            new_span = self.compute_total_span(new_ordering_index)
            # print("span:", new_span)
            if new_span < best_span:
                best_ordering = new_ordering
                best_span = new_span

            ordering = new_ordering
            ordering_index = new_ordering_index
            span = new_span

            i += 1
        return best_ordering


def from_cnf(variables: list[int], clauses: list[list[int]]) -> Hypergraph:
    hg = Hypergraph([v - 1 for v in variables])
    for clause in clauses:
        hg.add_edge([abs(literal) - 1 for literal in clause])
        # -1 for zero-based variables
    return hg


def test():
    import random

    m, s, e, c, a, r = 1, 2, 3, 4, 5, 6
    vars = [r, a, c, e, s, m]
    random.shuffle(vars)
    clauses = [
        [m],
        [-c, e],
        [-c, e],
        [-a, e],
        [-r, e],
        [-e, c, a, r],
        [-c, -a],
        [-c, -r],
        [-a, -r],
    ]
    hg = from_cnf(vars, clauses)
    ordering = hg.compute_force_ordering()
    print(ordering)


if __name__ == "__main__":
    test()
