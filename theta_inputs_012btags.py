def build_model(rootfile):
    files = rootfile
    model = build_model_from_rootfile(files, include_mc_uncertainties=True)
    model.fill_histogram_zerobins()
    model.set_signal_processes('zp*')
    for p in model.processes:
       model.add_lognormal_uncertainty('lumi', math.log(1.045), p)
       model.add_lognormal_uncertainty('btag', math.log(1.05), p)
    #model.add_lognormal_uncertainty('xs_bkg', math.log(1.50), 'other')
    model.add_lognormal_uncertainty('xs_top', math.log(1.15), 'ttbar')
    model.add_lognormal_uncertainty('qcd_norm', math.log(1.10), 'qcd')

    return model

model = build_model('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/theta_inputs_012btags.root')
model_summary(model)
plot_exp, plot_obs = asymptotic_cls_limits(model,use_data=False)
plot_exp.write_txt('/nfs/dust/cms/user/usaiem/ZprimeFullHad/justin.txt')
report.write_html('/nfs/dust/cms/user/usaiem/ZprimeFullHad/htmlout_justin')
