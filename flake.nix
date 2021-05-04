{
  description = "Development version of the next major version of gLabels";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
  flake-utils.lib.eachDefaultSystem (system:
  let pkgs = nixpkgs.legacyPackages.${system}; in
  rec {
    packages.glabels-qt = pkgs.qt5.mkDerivation {
      name = "glabels-qt";
      src = ./.;
      nativeBuildInputs = with pkgs; [ cmake ];
      buildInputs = with pkgs; [ qt5.qttools zlib ];
    };
    defaultPackage = packages.glabels-qt;
    apps.glabels-qt = flake-utils.lib.mkApp { drv = packages.glabels-qt; };
    defaultApp = apps.glabels-qt;
  });
}
