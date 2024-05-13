{ lib
, linkerScript
, rvv-codegen
, makeBuilder
, xLen
, vLen
, isFp
}:

let
  builder = makeBuilder { casePrefix = "codegen"; };
  makeCaseName = lib.replaceStrings [ "." ] [ "_" ];

  build = { rawCaseName, isFp }:
    builder rec {
      caseName = makeCaseName rawCaseName;

      includeArgs = [
        "-I${./override_include}"
        "-I${rvv-codegen}/include"
      ];

      dontUnpack = true;

      inherit isFp;

      buildPhase = ''
        runHook preBuild

        ${rvv-codegen}/bin/single \
          -VLEN "${toString vLen}" \
          -XLEN "${toString xLen}" \
          -repeat 16 \
          -testfloat3level 2 \
          -configfile ${rvv-codegen}/configs/${rawCaseName}.toml \
          -outputfile $pname.S

        # temporary fix, to be extended later
        if $CC $pname.S -T ${linkerScript} $includeArgs -o $pname.elf ; then
          echo "link with 4M SRAM succeded"
        else
          echo "link with 4M SRAM failed, use DDR instead"
          sed 's/>SRAM/>DDR/' ${linkerScript} > t1-ddr.ld
          $CC $pname.S -T t1-ddr.ld $includeArgs -o $pname.elf
        fi

        runHook postBuild
      '';

      meta.description = "test case '${caseName}' generated by codegen";
    };

  buildTestsFromFile = file: { isFp ? false }:
    with lib;
    let
      rawCaseNames = lib.splitString "\n" (lib.fileContents file);
    in
    (listToAttrs
      (map
        (rawCaseName: nameValuePair
          (makeCaseName rawCaseName)
          (build { inherit rawCaseName isFp; })
        )
        rawCaseNames));

  commonTests = buildTestsFromFile ./common.txt { };
  fpTests = buildTestsFromFile ./fp.txt { isFp = true; };

in
lib.recurseIntoAttrs (
    if isFp
    then commonTests // fpTests
    else commonTests
)

